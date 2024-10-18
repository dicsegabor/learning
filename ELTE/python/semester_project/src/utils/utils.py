import random
from sys import platform
import os


def random_bool() -> bool:
    return bool(random.getrandbits(1))


def random_float(floor: float = -2, ceiling: float = 2) -> float:
    return random.uniform(floor, ceiling)


def clear_console():
    if platform == "linux" or platform == "linux2" or platform == "darwin":
        os.system("clear")
    else:
        os.system("cls")
