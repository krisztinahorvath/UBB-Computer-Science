from board.board import Board

class BoardServices:
    def __init__(self, board):
        self.table = board.table

    def display(self):
        print(self.table.draw())
        print()

    def add_move_to_board(self, x, y, elem):
        self.table.rows[x, y] = elem

    def check_for_win(self, x, y):
        """
        Checks if one of the players one by placing a move on [x,y], checks all the cases
        :param x: row
        :param y: column
        :return: true/ false for winning
        """
        if self.diagonal_win_main(x, y) is not True and self.diagonal_secondary_win(x, y) is not True and self.row_win(x, y) is not True and self.column_win(x, y) is not True:
            return False
        return True

    def diagonal_win_main(self, x, y):
        """
        Checks if by making a move on position [x,y] the game is won on the main diagonal
        :param x: row
        :param y: column
        :return: if the game is won and the main diagonal is only X or O true/false
        """
        element = self.table.rows[x][y]
        for i in range(0, 3):
            if self.table.rows[i][i] != element:
                return False
        return True

    def diagonal_secondary_win(self, x, y):
        """
        Checks if by making a move on position [x,y] the game is won on the main diagonal
        :param x: row
        :param y: column
        :return: if the game is won and the secondary diagonal is only X or O, true/false
        """
        element = self.table.rows[x][y]
        for i in range(0, 3):
            if self.table.rows[i][3-1-i] != element:
                return False
        return True

    def row_win(self, x, y):
        """
        Checks if the game is won on the x row
        :param x: row
        :param y: column
        :return: if the game is won on the row x : true/false
        """
        element = self.table.rows[x][y]
        for i in range(0, 3):
            if self.table.rows[x][i] != element:
                return False
        return True

    def column_win(self, x, y):
        """
        Checks if the game is won on the y row
        :param x: row
        :param y: column
        :return: if the game is won in the row y, true/false
        """
        element = self.table.rows[x][y]
        for i in range(0, 3):
            if self.table.rows[i][y] != element:
                return False
        return True

    # def check_for_two_xs(self):
    #     """
    #     This function looks for two X's made by the human so that it doesn't let the human win, with only one move
    #     :return: the position where the computer should make the move
    #     """
    #     s = 0        # on the main diag
    #     for i in range(0, 3):
    #         nr = self.table.rows[i][i]
    #         if nr == 'X':
    #             s = s + 1
    #         elif
    #     if s == 2:
    #         return x, y

    def empty_pos_left(self):
        """
        Computes the number of empty positions left in the board
        :return: nr of empty pos left in the board
        """
        s = 0
        for i in range(0, 3):
            for j in range(0, 3):
                if self.table.rows[i][j] not in ['X', 'O']:
                    s = s + 1
        return s