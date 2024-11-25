import unittest
import time
from SubProcess import ChessEngine

class TestCheck(unittest.TestCase):
    def setUp(self):
        self.engine = ChessEngine("chess.exe")

    def tearDown(self):
        self.engine.close()

    def test_king_in_check(self):
        print("DEBUG: Running test_king_in_check...")

        # Moves that lead to a check situation
        moves = [(6, 4), (4, 4), (1, 5), (3, 5)]  # e2 to e4, b7 to b5

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
        self.assertEqual(game_condition, 1, "Game condition should indicate that the king is in check.")

if __name__ == "__main__":
    unittest.main()
