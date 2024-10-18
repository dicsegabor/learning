from devices.simulatable_device import SimulatableDeviceMixin
from devices.smart_device import SmartDevice
from utils import utils


class SecurityCamera(SmartDevice, SimulatableDeviceMixin):
    """
    Represents a security camera.
    """

    def __init__(self, id: str):
        super().__init__(id)
        self.status = True
        self.recording = False
        self.motion_detected = False

    def is_motion_detected(self) -> bool:
        if not self.status:
            return False
        return self.motion_detected

    def is_recording(self):
        if not self.status:
            return False
        return self.recording

    def start_recording(self):
        self.recording = True

    def stop_recording(self):
        self.recording = False

    def update_motion_detected(self):
        self.motion_detected = utils.random_bool()

    def __str__(self) -> str:
        return (
            super().__str__()
            + f" | Rec: {self.is_recording()}, Motion: {self.is_motion_detected()}"
        )

    def reset(self):
        self.turn_off()
        self.recording = False
        self.motion_detected = False

    def simulate_change(self):
        if self.get_status():
            self.motion_detected = utils.random_bool()
