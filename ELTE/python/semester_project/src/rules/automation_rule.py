from abc import abstractmethod


class AutomationRule:
    def __init__(self, name) -> None:
        self.name = name

    @abstractmethod
    def evaluate(self, automation_system):
        ...
