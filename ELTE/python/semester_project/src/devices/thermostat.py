from devices.simulatable_device import SimulatableDeviceMixin
from devices.smart_device import SmartDevice
from utils import utils


class Thermostat(SmartDevice, SimulatableDeviceMixin):
    lower_bound = 10
    upper_bound = 30

    def __init__(self, id: str, default_temperature=22):
        super().__init__(id)
        self.default_temperature = default_temperature
        self.temperature = default_temperature

    def set_temperature(self, temperature):
        if self.upper_bound < self.temperature < self.lower_bound:
            raise ValueError(
                f"The given temperature should be between {self.lower_bound}"
                + f" and {self.upper_bound}."
            )

        self.temperature = temperature

    def change_temperature(self, delta=float(1)):
        if self.upper_bound < self.temperature + delta < self.lower_bound:
            raise ValueError(
                f"The given temperature should be between {self.lower_bound}"
                + f" and {self.upper_bound}."
            )

        self.temperature += delta

    def __str__(self) -> str:
        return super().__str__() + f" | Temp: {self.temperature}"

    def reset(self):
        self.turn_off()
        self.temperature = self.default_temperature

    def simulate_change(self):
        self.change_temperature(utils.random_float())
