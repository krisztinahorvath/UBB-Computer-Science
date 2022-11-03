from board.validation import validation_of_pos


class MoveServices:
    def __init__(self, board):
        self.board = board

    def human_move(self, x, y):
        try:
            validation_of_pos(x, y)
            if self.board.empty_position(x, y) is False:
                raise ValueError("Illegal move, position already occupied!")
            else:
                self.board.add_move_to_board(x, y)
                if self.board.check_for_win(x, y) is True:
                    return True
                return False

        except ValueError as ve:
            raise ve

    def computer_move(self, x, y):
       pass