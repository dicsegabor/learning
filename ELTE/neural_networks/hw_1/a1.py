import unittest
from collections import defaultdict
import itertools

class UnknownPlayerException(Exception):
    pass

class BasketballEventsStore:
    def __init__(self) -> None:
        self.players = []
        self.events = defaultdict(list)

    def add_player(self,playername):
        self.players.append(playername)
        self.events[playername] = []

    def add_event(self, playername, event):
        if playername not in self.players: 
            raise UnknownPlayerException
        self.events[playername].append(event)

    def get_unique_actions(self) -> list:
        return list(set(itertools.chain.from_iterable(self.events.values()))) 

    def get_player_names_starting_with(self, ch) -> list:
        return [p for p in self.players if p.lower().startswith(ch.lower())]

    def get_total_passes_per_player(self) -> dict: 
        return {k:v.count('pass') for (k, v) in self.events.items()}

    def get_players_with_duplicate_actions(self) ->  list:
        return [k for (k,v) in self.events.items() if len(set(v)) < len(v)]

class TestBasketballEventsStore(unittest.TestCase):

    def setUp(self):
        self.stats_store = BasketballEventsStore()

    def test_add_event_unknown_player(self):
        with self.assertRaises(UnknownPlayerException):
            self.stats_store.add_event("Kareem Abdul-Jabbar", "field goal")
        
        try:
            self.stats_store.add_player("Kareem Abdul-Jabbar")
            self.stats_store.add_event("Kareem Abdul-Jabbar", "field goal")
        except UnknownPlayerException:
            self.fail("raised UnknownPlayerException, but player is already added")
        
    def test_get_unique_actions(self):
        self.stats_store.add_player("Kobe Bryant")
        self.assertEqual(len(self.stats_store.get_unique_actions()), 0)
        self.stats_store.add_event("Kobe Bryant", "pass")
        self.stats_store.add_event("Kobe Bryant", "field goal")

        unique_actions = self.stats_store.get_unique_actions()
        self.assertEqual(len(unique_actions), 2)
        self.assertTrue("pass" in unique_actions)
        self.assertTrue("field goal" in unique_actions)

        self.stats_store.add_player("LeBron James")
        self.stats_store.add_event("LeBron James", "pass")
        self.assertEqual(len(self.stats_store.get_unique_actions()), 2)
        self.stats_store.add_event("LeBron James", "tackle")

        unique_actions2 = self.stats_store.get_unique_actions()
        self.assertEqual(len(unique_actions2), 3)
        self.assertTrue("pass" in unique_actions2)
        self.assertTrue("field goal" in unique_actions2)
        self.assertTrue("tackle" in unique_actions2)

    def test_get_player_names_starting_with(self):
        self.stats_store.add_player("Michael Jordan")
        self.assertEqual(self.stats_store.get_player_names_starting_with("M"), ["Michael Jordan"])
        self.assertEqual(self.stats_store.get_player_names_starting_with("m"), ["Michael Jordan"])
        self.stats_store.add_player("Ja Morant")
        self.assertEqual(self.stats_store.get_player_names_starting_with("m"), ["Michael Jordan"])
        self.stats_store.add_player("Mitch Richmond")
        
        m_players = self.stats_store.get_player_names_starting_with("M")
        self.assertTrue("Michael Jordan" in m_players)
        self.assertTrue("Mitch Richmond" in m_players)
        self.assertEqual(len(m_players), 2)

    def test_get_total_passes_per_player(self):
        self.stats_store.add_player("James Harden")
        self.assertEqual(self.stats_store.get_total_passes_per_player(), {"James Harden": 0})
        self.stats_store.add_event("James Harden", "pass")
        self.stats_store.add_event("James Harden", "field goal")
        self.stats_store.add_event("James Harden", "pass")
        self.assertEqual(self.stats_store.get_total_passes_per_player(), {"James Harden": 2})
        self.stats_store.add_player("Russell Westbrook")
        self.stats_store.add_event("Russell Westbrook", "pass")
        self.stats_store.add_event("Russell Westbrook", "tackle")
        self.stats_store.add_event("Russell Westbrook", "free throw")

        passes_per_player = self.stats_store.get_total_passes_per_player()
        self.assertEqual(passes_per_player["Russell Westbrook"], 1)
        self.assertEqual(passes_per_player["James Harden"], 2)

    def test_get_players_with_duplicate_actions(self):
        self.stats_store.add_player("Michael Jordan")
        self.assertEqual(self.stats_store.get_players_with_duplicate_actions(), [])
        self.stats_store.add_event("Michael Jordan", "free throw")
        self.assertEqual(self.stats_store.get_players_with_duplicate_actions(), [])
        self.stats_store.add_player("Shaquille O'Neal")
        self.assertEqual(self.stats_store.get_players_with_duplicate_actions(), [])
        self.stats_store.add_event("Shaquille O'Neal", "tackle")
        self.stats_store.add_event("Shaquille O'Neal", "pass")
        self.stats_store.add_event("Michael Jordan", "pass")
        self.stats_store.add_event("Shaquille O'Neal", "tackle")
        self.assertEqual(self.stats_store.get_players_with_duplicate_actions(), ["Shaquille O'Neal"])
        self.stats_store.add_event("Michael Jordan", "pass")
        self.assertEqual(set(self.stats_store.get_players_with_duplicate_actions()), {"Shaquille O'Neal", "Michael Jordan"})

def suite():
    suite = unittest.TestSuite()
    testfuns = ["test_add_event_unknown_player", "test_get_unique_actions",
                "test_get_player_names_starting_with", "test_get_total_passes_per_player", 
                "test_get_players_with_duplicate_actions"]
    [suite.addTest(TestBasketballEventsStore(fun)) for fun in testfuns]
    return suite

runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite())
