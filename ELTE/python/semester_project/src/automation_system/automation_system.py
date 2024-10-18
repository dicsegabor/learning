from devices.simulatable_device import SimulatableDeviceMixin
from devices.smart_device import SmartDevice
from rules.automation_rule import AutomationRule
from .device_loader import load_devices_from_json


class AutomationSystem:
    """
    This represents an automation system.
    Variables:
        devices: list[SmartDevice]
        rules: list [AutomationRule]
    """

    def __init__(self) -> None:
        self.devices: list[SmartDevice]
        self.devices = []
        self.rules: list[AutomationRule]
        self.rules = []

    def add_device(self, device: SmartDevice):
        """Add a device if it is not in the system. (checks it by id)"""
        if device not in self.devices:
            self.devices.append(device)

    def discover_devices(self):
        """Loads devies from a json file, within the project folder."""
        for device in load_devices_from_json("devices.json"):
            self.add_device(device)

    def execute_automation_rules(self):
        """Runs all the automation rules from the rules list."""
        for automation_rule in self.rules:
            automation_rule.evaluate(self)

    def get_device_by_id(self, id: str) -> SmartDevice:
        """
        Returns a device by id.
        Raises LookupError if not found.
        """
        for d in self.devices:
            if d.id == id:
                return d

        raise LookupError(f"No device found with ID: {id}")

    def remove_device(self, id: str):
        """
        Removes a device by id.
        Raises a lookup error if not found.
        """
        for device in self.devices:
            if device.id == id:
                self.devices.remove(device)
                return device

        raise LookupError(f"No device found with ID: {id}")

    def start_simulations(self):
        """
        For every device, if it is simulatable, starts its simulation.
        """
        for device in self.devices:
            if isinstance(device, SimulatableDeviceMixin):
                device.start_simulation()

    def stop_simulations(self):
        """
        Stops the simulation processes.
        """
        for device in self.devices:
            if isinstance(device, SimulatableDeviceMixin):
                device.stop_simulation()
