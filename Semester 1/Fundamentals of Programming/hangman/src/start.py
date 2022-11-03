import pickle

from src.ui.ui import UI
from src.controller.functionalities.functionalities import Controller
# f = open("repository/sentences.txt", "w")
# file_path = r"C:\Users\krisz\PycharmProjects\pythonProject\src\repository\sentence.bin"

# with open(file_path, "wb") as f:
#     pickle.dump(["anna has apples", "patricia has pears", "cars are fast", "planes are quick",
#                               "the quick brown fox jumps over the lazy dog"], f)
# f.close()

ui = UI(Controller("repository/sentences.txt"))
# ui = UI(Controller(file_path))
ui.start()


# anna has apples
# patricia has pears
# cars are fast
# planes are quick
# the quick brown fox jumps over the lazy dog
