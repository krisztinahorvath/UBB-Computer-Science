from src.ui.prints import Prints
from src.controller.functionalities.validations import ValidationError


class UI:
    def __init__(self, controller):
        self.controller = controller
        self.prints = Prints()

    def start(self):
        self.prints.console_print()
        option = input("Option:")
        just_started = 1
        while True:
            if option == "add":
                sentence = input("The sentence that you would like to add: ")
                try:
                    self.controller.add_sentence(sentence)
                    print("Sentence added successfully!")
                    self.prints.console_print()
                    option = input("Option:")
                except ValidationError as ve:
                    print(ve)
                    self.prints.console_print()
                    option = input("Option:")
                except IOError as ve:
                    print(ve)
                    self.prints.console_print()
                    option = input("Option:")

            elif option == "play":
                if just_started == 1:
                    print("Game mode begins!\nOutput: " +
                          '"' + str(self.controller.sentence_in_game) + '"' + ' - "' + str(self.controller.hangman) + '"')
                    just_started = 0
                else:
                    letter = input("Your guess is: ")
                    letter.strip()
                    letter.lower()
                    status = self.controller.letter_check(letter)
                    if status == "human":
                        print('"' + str(self.controller.sentence_in_game) + '"' + ' - "YOU WON!"')
                        return
                    elif status == "computer":
                        print('"' + str(self.controller.sentence_in_game) + '"' + ' - "' + str(
                            self.controller.hangman) + '"' + "  -  YOU LOST!")
                        return
                    else:
                        print('"' + str(self.controller.sentence_in_game) + '"' + ' - "' + str(self.controller.hangman) + '"')
            else:
                print("Invalid command!")
                self.prints.console_print()
                option = input("Option:")

