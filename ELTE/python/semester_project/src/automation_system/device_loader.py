import json
from devices.thermostat import Thermostat
from devices.security_camera import SecurityCamera
from devices.smart_light import SmartLight


def custom_decoder(obj):
    """
    Decodes a string into a class type.
    Only into my own device types.
    """
    if "type" in obj:
        class_type = obj.pop("type")
        if class_type == "SmartLight":
            return SmartLight(**obj)
        elif class_type == "Thermostat":
            return Thermostat(**obj)
        elif class_type == "SecurityCamera":
            return SecurityCamera(**obj)
    return obj


def load_devices_from_json(path: str):
    """
    Loads in the json file.
    Every item should have a 'type' record,
    so it can be recognized as a class.
    """
    with open(path, "r") as file:
        return json.load(file, object_hook=custom_decoder)
