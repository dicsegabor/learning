from automation_system.automation_system import AutomationSystem
from rules.light_motion_rule import LightMotionRule

from ui.menu import Menu


def main():
    automation_system = AutomationSystem()
    automation_system.discover_devices()

    automation_system.rules.append(LightMotionRule("Rule_1"))
    automation_system.start_simulations()

    menu = Menu("Automation System", automation_system)
    menu.show()

    automation_system.stop_simulations()


if __name__ == "__main__":
    main()
