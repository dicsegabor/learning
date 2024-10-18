
import numpy as np

# Generate a NumPy array with random numbers
arr = np.random.randint(1, 100, 10)

# Choose two random numbers
indices = np.random.choice(len(arr), 2, replace=False)
chosen_numbers = arr[indices]

# Create a subset with equal-sized elements
subset = arr[arr == chosen_numbers[0]][:len(arr[arr == chosen_numbers[1]])]

print("Original Array:", arr)
print("Chosen Numbers:", chosen_numbers)
print("Subset with Equal-sized Elements:", subset)
