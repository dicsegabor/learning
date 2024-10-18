from .automation_rule import AutomationRule
from automation_system.automation_system import AutomationSystem
from devices.security_camera import SecurityCamera
from devices.smart_light import SmartLight


class LightMotionRule(AutomationRule):
    def __init__(self, name) -> None:
        super().__init__(name)

    def evaluate(self, automation_system: AutomationSystem):
        motion_detected = any(
            device.is_motion_detected()
            for device in automation_system.devices
            if device is SecurityCamera
        )

        if motion_detected:
            for device in automation_system.devices:
                if isinstance(device, SmartLight):
                    device.set_brightness(100)
                    device.turn_on()
