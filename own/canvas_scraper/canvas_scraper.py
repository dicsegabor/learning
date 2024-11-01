import json
import time
import keyring
from getpass import getpass
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait, Select
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import sys

# Constants
SERVICE_NAME = "CanvasScraper"
USERNAME_KEY = "username"
PASSWORD_KEY = "password"

# Setup WebDriver
def setup_webdriver():
    service = Service(ChromeDriverManager().install())
    return webdriver.Chrome(service=service)

# Store credentials in keyring
def store_credentials():
    username = input("Enter your Neptun ID: ")
    password = getpass("Enter your password: ")
    keyring.set_password(SERVICE_NAME, USERNAME_KEY, username)
    keyring.set_password(SERVICE_NAME, PASSWORD_KEY, password)
    print("Credentials stored securely.")

# Retrieve credentials from keyring
def get_credentials():
    username = keyring.get_password(SERVICE_NAME, USERNAME_KEY)
    password = keyring.get_password(SERVICE_NAME, PASSWORD_KEY)
    if not username or not password:
        print("No credentials found. Please store them first.")
        store_credentials()
        username = keyring.get_password(SERVICE_NAME, USERNAME_KEY)
        password = keyring.get_password(SERVICE_NAME, PASSWORD_KEY)
    return username, password

# Check for login error
def check_login_error(driver):
    try:
        error_element = driver.find_element(By.CLASS_NAME, "error-title")
        if "Incorrect Neptun ID or password" in error_element.text:
            print("Login failed. Incorrect credentials.")
            keyring.delete_password(SERVICE_NAME, USERNAME_KEY)
            keyring.delete_password(SERVICE_NAME, PASSWORD_KEY)
            print("Stored credentials have been deleted. Please re-enter.")
            return False
    except Exception:
        return True

# Log in with retry logic
def login(driver, quiz_url):
    attempts = 2
    for attempt in range(attempts):
        username, password = get_credentials()
        driver.get(quiz_url)

        # Wait and click the login button
        WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.LINK_TEXT, "Belépés Neptun hozzáféréssel"))
        ).click()

        # Input credentials
        WebDriverWait(driver, 10).until(
            EC.visibility_of_element_located((By.ID, "username_neptun"))
        ).send_keys(username)
        driver.find_element(By.ID, "password_neptun").send_keys(password)

        # Submit the login form
        driver.find_element(By.CLASS_NAME, "submit-button").click()

        # Check for login success
        if check_login_error(driver):
            print("Login successful.")
            return True
        elif attempt < attempts - 1:
            print("Retrying login with new credentials...")
            store_credentials()

    print("Failed to login after multiple attempts.")
    return False

# Extract matching question data
def extract_matching_data(driver):
    question_text = driver.find_element(By.CLASS_NAME, "question_text").text
    pairs = [
        {
            "label": pair.find_element(By.TAG_NAME, "label").text,
            "options": [option.text for option in Select(pair.find_element(By.TAG_NAME, "select")).options if option.text != "[ Válasszon ]"]
        }
        for pair in driver.find_elements(By.CLASS_NAME, "answer")
    ]
    return {"question": question_text, "type": "matching", "pairs": pairs}

# Extract standard question data
def extract_standard_data(driver):
    question_text = WebDriverWait(driver, 10).until(
        EC.visibility_of_element_located((By.CLASS_NAME, "question_text"))
    ).text
    answers = driver.find_elements(By.CLASS_NAME, "answer")
    question_type = "multiple-choice" if any(answer.find_element(By.XPATH, ".//input[@class='question_input']").get_attribute("type") == "checkbox" for answer in answers) else "single-choice"
    return {
        "question": question_text,
        "type": question_type,
        "answers": [answer.find_element(By.CLASS_NAME, "answer_label").text for answer in answers]
    }

# Scrape each question
def scrape_question(driver, quiz_data):
    try:
        question_class = driver.find_element(By.CLASS_NAME, "display_question").get_attribute("class")
        question_data = extract_matching_data(driver) if "matching_question" in question_class else extract_standard_data(driver)
        quiz_data.append(question_data)
    except Exception as e:
        print("Error extracting question data:", e)

# Scrape the entire quiz
def scrape_quiz(driver):
    quiz_data = []
    sanitized_title = "".join(c if c.isalnum() else "_" for c in WebDriverWait(driver, 10).until(
        EC.visibility_of_element_located((By.ID, "quiz_title"))
    ).text or "quiz_data")

    try:
        WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.CLASS_NAME, "take_quiz_button"))).click()
    except Exception:
        print("Could not find or click the 'Take Quiz' button.")

    while True:
        scrape_question(driver, quiz_data)
        try:
            driver.find_element(By.CLASS_NAME, "next-question").click()
            time.sleep(2)
        except Exception:
            print("No more questions.")
            break

    with open(f"{sanitized_title}.json", "w", encoding="utf-8") as f:
        json.dump(quiz_data, f, ensure_ascii=False, indent=4)
    print(f"Quiz data saved to {sanitized_title}.json")

# Main function
def main(quiz_url):
    driver = setup_webdriver()
    if login(driver, quiz_url):
        scrape_quiz(driver)
    driver.quit()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python canvas_scraper.py <quiz_url>")
    else:
        main(sys.argv[1])
