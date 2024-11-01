import os
import shutil

def remove_venv_dirs(start_path='.'):
    """
    Recursively find and remove all 'venv' directories starting from the given path.
    
    Args:
        start_path (str): The root directory to start searching from. Defaults to current directory.
    """
    for root, dirs, files in os.walk(start_path):
        if 'venv' in dirs:
            venv_path = os.path.join(root, 'venv')
            print(f"Removing {venv_path}...")
            shutil.rmtree(venv_path)
            # Remove 'venv' from dirs to prevent further os.walk() exploration into this directory
            dirs.remove('venv')  

# Run the script from the current directory
remove_venv_dirs()
