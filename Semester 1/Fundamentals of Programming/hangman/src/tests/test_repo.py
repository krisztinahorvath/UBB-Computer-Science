import unittest
from src.repository.repo import Repository
import copy
import os.path


class TestRepository(unittest.TestCase):
    def setUp(self) -> None:
        self.file_name = r"C:\Users\krisz\PycharmProjects\pythonProject\src\repository\sentences.txt"
        self.repo = Repository(self.file_name)

    def tearDown(self) -> None:
        pass

    def test_load_file(self):
        self.repo._file_name = "sent.txt"
        with self.assertRaises(IOError) as e:
            self.repo.load_file()
        # self.assertEqual(str(e.exception))
        self.assertEqual(self.repo.sentence_list, ["anna has apples", "patricia has pears", "cars are fast", "planes are quick",
                          "the quick brown fox jumps over the lazy dog"])
        self.assertTrue(os.path.exists(self.file_name))
        self.assertFalse(os.path.exists(self.repo._file_name))

    def test_save_file(self):
        old_file = copy.deepcopy(self.repo.sentence_list)

        self.repo.add_sentence("Anna has cotlet de porc")
        self.repo.add_sentence("mariana exista")
        self.repo.add_sentence("exista sapte bocanci")

        self.repo.save_file()
        self.repo.load_file()
        self.assertTrue("Anna has cotlet de porc" in self.repo.sentence_list)
        self.assertTrue("mariana exista" in self.repo.sentence_list)
        self.assertTrue("exista sapte bocanci" in self.repo.sentence_list)

        self.repo._sentence_list = copy.deepcopy(old_file)
        self.repo.save_file()

    def test_add_sentence(self):
        old_file = copy.deepcopy(self.repo.sentence_list)

        self.repo.add_sentence("Anna has seven lambs")
        self.assertEqual(str(self.repo.sentence_list[-1]), "Anna has seven lambs")

        self.repo.add_sentence("Anna has four dolls")
        self.assertEqual(str(self.repo.sentence_list[-1]), "Anna has four dolls")

        self.repo._sentence_list = copy.deepcopy(old_file)
        self.repo.save_file()

    def test_sentence_list(self):
        self.assertEqual(self.repo.sentence_list,
                         ["anna has apples", "patricia has pears", "cars are fast", "planes are quick",
                          "the quick brown fox jumps over the lazy dog"])


if __name__ == "__main__":
    unittest.main()