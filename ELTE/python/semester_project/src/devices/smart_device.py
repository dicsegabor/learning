from abc import ABC, abstractmethod


class SmartDevice(ABC):
    """
    Abstract base class for devices.
    Implements specific eq and hash functions based on id parameter.

    Variables:
        status: bool -> False by default
        id: str

    It has one abstract method:
        reset(), that is different for every child class
    """

    def __init__(self, id: str):
        self.status = False
        self.id = id

    def __eq__(self, other: object) -> bool:
        """Two devices are equal if their id and type is equal."""
        if isinstance(other, SmartDevice):
            return self.id == other.id
        return False

    def __hash__(self) -> int:
        return hash(self.id)

    def get_status(self) -> bool:
        return self.status

    def toggle_device(self):
        self.status = not self.status

    def turn_on(self):
        self.status = True

    def turn_off(self):
        self.status = False

    def __str__(self) -> str:
        return f"{self.id}: {'On' if self.status else 'Off'}"

    @abstractmethod
    def reset(self):
        ...
