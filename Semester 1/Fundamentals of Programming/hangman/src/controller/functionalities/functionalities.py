import copy
from random import choice
from src.repository.repo import Repository
from copy import deepcopy
from src.controller.functionalities.validations import ValidationError, Validations
"""
Controller class that has all the functionalities needed to play the game.
"""


class Controller:
    def __init__(self, file_name):
        self.repo = Repository(file_name)
        self.sentence_solution = self.random_sentence()
        self.sentence_in_game = self.codify_sentence()
        self.hangman = ""

    def random_sentence(self):
        """
        Chooses a random sentence from the sentence list read from the input file
        :return: the random sentence
        """
        return choice(self.repo.sentence_list)

    def add_sentence(self, sentence):
        """
        Adds a given sentence to the sentence list, and saves it to the sentences.txt file
        :param sentence: sentence given by the user
        """
        try:
            sentence = sentence.strip()
            valid = Validations(sentence, self.repo.sentence_list)
            valid.valid_sentence()
            self.repo.add_sentence(sentence)
        except ValidationError as ve:
            raise ve
        except IOError as ve:
            raise ve

    def codify_sentence(self):
        """
        Codifies the randomly selected sentence so that the user can play, codifies it hangman style
        :return:
        """
        new_sentence = ""
        sent = deepcopy(self.sentence_solution)
        letters_to_be_shown = ""
        for word in sent.split(" "):
            letters_to_be_shown = letters_to_be_shown + word[0] + word[-1]
        for word in sent.split(" "):
            new_sentence = new_sentence + word[0]
            for i in range(1, len(word)-1):
                if word[i] in letters_to_be_shown:
                    new_sentence = new_sentence + word[i]
                else:
                    new_sentence = new_sentence + '_'
            new_sentence = new_sentence + word[-1] + ' '

        new_sentence = new_sentence.strip()
        return new_sentence

    def game_won_human(self):
        """
        Checks if the human won the game by guessing all the letters from the sentence
        :return: 1 - human won, 0 - otherwise
        """
        if self.sentence_solution == self.sentence_in_game:
            return 1
        return 0

    def game_won_computer(self):
        """
        Checks if the computer won the game by the mistakes made by the human
        :return: 1 - computer won, 0 - otherwise
        """
        if self.hangman == "hangman":
            return 1
        return 0

    def letter_found(self, letter):
        """
        Checks if a letter given by the player appears in the sentence played on or not
        :param letter: letter given by the user
        :return: 1 - if letter appears in the sentence, 0 - otherwise
        """
        if letter in self.sentence_solution and letter not in self.sentence_in_game:
            return 1
        return 0

    def reveal_letters(self, letter):
        """
        Reveals the letter "letter" which was guessed by the human during the game in the sentence that they're
        playing on
        :param letter: letter given by the user
        """
        new_sentence = ""
        for i in range(0, len(self.sentence_solution)):
            if letter == self.sentence_solution[i]:
                new_sentence = new_sentence + letter
            else:
                new_sentence = new_sentence + self.sentence_in_game[i]
        self.sentence_in_game = copy.deepcopy(new_sentence)

    def hangman_completion(self):
        """
        Adds a letter to the word hangman: ex: h => ha, ha=> han, ...,hangma => hangman
        :return:
        """
        s = "hangman"
        self.hangman = self.hangman + s[len(self.hangman)]

    def letter_check(self, letter):
        """
        Checks if the letter given by the user is correct, and verifies if the user or computer won
        :return: human - user won, computer - user lost, continue - otherwise
        """
        if self.letter_found(letter) == 1:
            self.reveal_letters(letter)
            if self.game_won_human() == 1:
                return "human"
        else:
            self.hangman_completion()
            if self.game_won_computer() == 1:
                return "computer"
        return "continue"



