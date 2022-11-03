import unittest
from src.controller.functionalities.functionalities import Controller
from src.controller.functionalities.validations import ValidationError, Validations
import copy


class TestController(unittest.TestCase):
    def setUp(self) -> None:
        file_name = r"C:\Users\krisz\PycharmProjects\pythonProject\src\repository\sentences.txt"
        self.controller = Controller(file_name)

    def tearDown(self) -> None:
        pass

    def test_add_sentence(self):

        old_file = copy.deepcopy(self.controller.repo.sentence_list)

        self.controller.add_sentence("Anna has seven lambs")
        self.assertEqual(str(self.controller.repo.sentence_list[-1]), "Anna has seven lambs")

        self.controller.add_sentence("Anna has four dolls")
        self.assertEqual(str(self.controller.repo.sentence_list[-1]), "Anna has four dolls")

        with self.assertRaises(ValidationError) as ve:
            self.controller.add_sentence("anna has apples")
        self.assertEqual(str(ve.exception),  "\tInvalid input! The sentence that you are trying to add already exists!")
        self.assertEqual(str(self.controller.repo.sentence_list[-1]), "Anna has four dolls")

        self.controller.repo._sentence_list = copy.deepcopy(old_file)
        self.controller.repo.save_file()

    def test_codify_sentence(self):
        self.controller.sentence_solution = "Anna has apples"
        self.assertEqual(str(self.controller.codify_sentence()), "A__a has a____s")

        self.controller.sentence_solution = "the quick brown fox jumps over the lazy dog"
        self.assertEqual(str(self.controller.codify_sentence()), "t_e q___k bro_n fox j___s o_er t_e l__y dog")

        self.controller.sentence_solution = "The panda has pants"
        self.assertEqual(str(self.controller.codify_sentence()), "The pa__a has pa__s")

    def test_game_won_human(self):
        self.controller.sentence_in_game = "anna has apples"
        self.controller.sentence_solution = "anna has apples"
        self.assertEqual(self.controller.game_won_human(), 1)

        self.controller.sentence_in_game = "anna has apple_"
        self.controller.sentence_solution = "anna has apples"
        self.assertEqual(self.controller.game_won_human(), 0)

    def test_game_won_computer(self):
        self.controller.hangman = "hangman"
        self.assertEqual(self.controller.game_won_computer(), 1)

        self.controller.hangman = "hangma"
        self.assertEqual(self.controller.game_won_computer(), 0)

    def test_letter_found(self):
        self.controller.sentence_solution = "Anna has apples"
        self.controller.sentence_in_game = "A__a has a__les"

        self.assertEqual(self.controller.letter_found("n"), 1)
        self.assertEqual(self.controller.letter_found("p"), 1)
        self.assertEqual(self.controller.letter_found("k"), 0)
        self.assertEqual(self.controller.letter_found("b"), 0)

    def test_reveal_letters(self):
        self.controller.sentence_solution = "Anna has apples"
        self.controller.sentence_in_game = "A__a has a__les"
        self.controller.reveal_letters("n")
        self.assertEqual(self.controller.sentence_in_game, "Anna has a__les")

        self.controller.reveal_letters("p")
        self.assertEqual(self.controller.sentence_in_game, "Anna has apples")

    def test_hangman_completion(self):
        self.controller.hangman = ""
        self.controller.hangman_completion()
        self.assertEqual(self.controller.hangman, "h")

        self.controller.hangman_completion()
        self.assertEqual(self.controller.hangman, "ha")

    def test_letter_check(self):
        self.controller.sentence_solution = "Anna has apples"
        self.controller.sentence_in_game = "A__a has a__les"

        self.assertEqual(self.controller.letter_check("n"), "continue")
        self.assertEqual(self.controller.letter_check("p"), "human")

        self.controller.hangman = "hangma"
        self.controller.sentence_in_game = "A__a has a__les"
        self.assertEqual(self.controller.letter_check("e"), "computer")


class TestValidations(unittest.TestCase):
    def setUp(self) -> None:
        self.sentence_list = ["anna has apples", "patricia has pears", "cars are fast", "planes are quick",
                              "the quick brown fox jumps over the lazy dog"]

    def tearDown(self) -> None:
        pass

    def test_duplicate_sentence(self):
        # testing invalid input
        with self.assertRaises(ValidationError) as ve:
            valid = Validations("anna has apples", self.sentence_list)
            valid.duplicate_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! The sentence that you are trying to add already exists!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations("patricia has pears", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! The sentence that you are trying to add already exists!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations("the quick brown fox jumps over the lazy dog      ", self.sentence_list)
            valid.duplicate_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! The sentence that you are trying to add already exists!")

        # testing valid input
        valid1 = Validations("anna has apple", self.sentence_list)
        valid1.duplicate_sentence()

        valid2 = Validations("the     quick brown fox jumps over the lazy dog      ", self.sentence_list)
        valid2.duplicate_sentence()

    def test_valid_sentence(self):
        with self.assertRaises(ValidationError) as ve:
            valid = Validations("an", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! "
                                      "The sentence must contain at least one word of at least three letters!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations(" ", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! "
                                      "The sentence must contain at least one word of at least three letters!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations("", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! "
                                      "The sentence must contain at least one word of at least three letters!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations("ana ha apples", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! Not all words have three letters!")

        with self.assertRaises(ValidationError) as ve:
            valid = Validations("a na ", self.sentence_list)
            valid.valid_sentence()
        self.assertEqual(str(ve.exception), "\tInvalid input! Not all words have three letters!")


if __name__ == "__main__":
    unittest.main()
