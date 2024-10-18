import threading
from consolemenu import ConsoleMenu
from consolemenu.items import FunctionItem
from consolemenu.multiselect_menu import SubmenuItem

from utils.utils import clear_console
from automation_system.automation_system import AutomationSystem
from devices.smart_device import SmartDevice


class Menu:
    def __init__(self, name: str, automation_system: AutomationSystem) -> None:
        self.automation_system = automation_system
        self.menu = ConsoleMenu(name)
        self._create_menu()

    def show(self):
        self.menu.show()

    def _create_menu(self):
        self.menu.append_item(
            FunctionItem("Show status", self._show_autsys_status)
        )
        self.menu.append_item(
            SubmenuItem(
                "Toggle devices", self._create_on_off_menu(), self.menu
            )
        )

    def _create_on_off_menu(self) -> ConsoleMenu:
        menu = ConsoleMenu("Toggle devices")
        for d in self.automation_system.devices:
            menu.append_item(
                FunctionItem(
                    f"{d.id}: {'On' if d.get_status() else 'Off'}",
                    self._toggle_device_and_refresh,
                    [menu, d],
                )
            )

        return menu

    def _toggle_device_and_refresh(
        self, menu: ConsoleMenu, device: SmartDevice
    ):
        device.toggle_device()

        exit = menu.items[-1]
        menu.items.clear()
        for d in self.automation_system.devices:
            menu.append_item(
                FunctionItem(
                    super(type(d), d).__str__(),
                    self._toggle_device_and_refresh,
                    [menu, d],
                )
            )

        menu.append_item(exit)

    def _show_autsys_status(self):
        while True:
            clear_console()
            print("(It refreshes every second, hold enter to exit :)\n")
            for d in self.automation_system.devices:
                print(d)

            input_thread = threading.Thread(target=input)
            input_thread.start()
            input_thread.join(1)

            if not input_thread.is_alive():
                break
