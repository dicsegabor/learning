import threading
import time
from utils import utils


class SimulatableDeviceMixin:
    """
    Extends the fuctionality of a device, so it can be simulated.
    Variables:
        running: bool -> if the simulation is runnning
        simulation_thread: Thread

    Every class that uses this must define the simulate_change() method.
    """

    runnning: bool
    simulation_thread: threading.Thread

    def simulate_change(self):
        """
        Abstract method, should be implemented by child classes.
        """
        ...

    def _simulation_loop(self):
        """
        Runs the simulate_change() method, every
        random(0,5) seconds, while self.running is true
        """
        while self.runnning:
            self.simulate_change()
            time.sleep(utils.random_float(0, 5))

    def start_simulation(self):
        """
        Starts the _simulation_loop() method in a separate thread.
        """
        self.runnning = True
        self.simulation_thread = threading.Thread(target=self._simulation_loop)
        self.simulation_thread.start()

    def stop_simulation(self):
        """
        Joins the simulation_thread.
        """
        self.runnning = False
        self.simulation_thread.join()
