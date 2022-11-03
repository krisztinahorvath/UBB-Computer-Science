class Game:
    def __init__(self, boardServices, services):
        self.board = boardServices  # board services
        self.human_turn = True
        self.computer_turn = False
        self.services = services

    def game_begins(self):
        win_human = False
        win_computer = False
        self.board.display()
        print_once = 1
        while True:
            var = self.placement_phase()
            if var is False:
                print("Game ends!")
                return
            else:
                if print_once == 1:
                    print("Movement phase begins!")
                    print_once = 0
                self.movement_phase()

    def placement_phase(self):
        """
        The placement phase where the computer and human adds their moves
        :return: true if the game is won, false if it will continue with the movement phase
        """
        win_human = False
        win_computer = False
        self.human_turn = True
        self.computer_turn = False
        empty_pos_left = self.board.empty_pos_left()
        while win_human is False and win_computer is False and empty_pos_left <= 7:
            if self.human_turn is True:
                try:
                    print("Please introduce the position of your move!")
                    x = input("x = ")
                    y = input("y = ")
                    if self.services.human_move(x, y) is True:
                        win_human = True
                        print("Congrats you won!")
                        return False

                except ValueError as ve:
                    print(ve)
                self.human_turn = False
                self.computer_turn = True
                self.board.display()
            else:

                # todo make computer move
                self.human_turn = True
                self.computer_turn = False

        if empty_pos_left == 8:
            print("No victory")
            return False
        else:
            return True

    def movement_phase(self):
        pass
