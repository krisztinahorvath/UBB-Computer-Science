from game.game import Game
from board.board import Board
from service.moveServices import MoveServices

start_game = Game(Board(), MoveServices(Board()))
start_game.game_begins()

