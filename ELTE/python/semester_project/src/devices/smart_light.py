from devices.smart_device import SmartDevice


class SmartLight(SmartDevice):
    lower_bound = 0
    upper_bound = 100

    def __init__(self, id: str):
        super().__init__(id)
        self.brightness = self.upper_bound

    def set_brightness(self, brightness: int):
        if self.upper_bound < brightness < self.lower_bound:
            raise ValueError(
                f"Brightness should be a value between {self.lower_bound}"
                + f" and {self.upper_bound}."
            )

        self.brightness = brightness

    def __str__(self) -> str:
        return super().__str__() + f" | Brightness: {self.brightness}"

    def reset(self):
        self.turn_off()
        self.brightness = self.upper_bound
