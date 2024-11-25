import unittest
import time
from SubProcess import ChessEngine

class TestCheckmate(unittest.TestCase):
    def setUp(self):
        self.engine = ChessEngine("chess.exe")

    def tearDown(self):
        self.engine.close()

    def test_king_in_checkmate(self):
        print("DEBUG: Running test_king_in_checkmate...")

        # Moves that lead to a checkmate situation
        moves = [(6, 4), (4, 4), (1, 5), (3, 5), (7, 3), (3, 7)]  # e2 to e4, f7 to f5, d1 to h5

        for index, (row, col) in enumerate(moves):
            game_condition, _, _, _ = self.engine.select_piece(row, col)

            # Introduce a delay to allow the C engine to update
            time.sleep(0.5)

            game_condition, board, sides, highlights = self.engine.move_piece(row, col)

            # Debugging the board state after each move
            print(f"DEBUG: Board after move {index + 1} ({(row, col)}):\n{board}")
            print(f"DEBUG: Game condition after move {index + 1}: {game_condition}")

            # Introduce a delay to allow the C engine to update
            time.sleep(0.5)

        # Assertions
        print(f"DEBUG: Final board state before checkmate check:\n{board}")
        self.assertEqual(game_condition, 2, "Game condition should indicate checkmate.")

if __name__ == "__main__":
    unittest.main()
