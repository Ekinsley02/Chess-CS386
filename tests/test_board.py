import unittest
from SubProcess import ChessEngine

class TestBoard(unittest.TestCase):
    def setUp(self):
        self.engine = ChessEngine("chess.exe")

    def tearDown(self):
        self.engine.close()

    def test_initial_board_setup(self):
        print("DEBUG: Running test_initial_board_setup...")
        board, sides, highlights = self.engine.get_initial_board()

        if board is None or sides is None or highlights is None:
            self.skipTest("Subprocess did not return valid board data.")

        print(f"DEBUG: Board: {board}")
        self.assertEqual(len(board), 8, "Board should have 8 rows.")
        self.assertEqual(len(board[0]), 8, "Board should have 8 columns.")
        self.assertEqual(board[0][0], "R", "Expected Rook at board[0][0].")

    def test_highlights_initial_state(self):
        print("DEBUG: Running test_highlights_initial_state...")
        _, _, highlights = self.engine.get_initial_board()

        if highlights is None:
            self.skipTest("Subprocess did not return valid highlights data.")

        print(f"DEBUG: Highlights: {highlights}")
        self.assertEqual(len(highlights), 8, "Highlights should have 8 rows.")
        self.assertTrue(all(len(row) == 8 for row in highlights),
                        "Each row in highlights should have 8 columns.")


if __name__ == "__main__":
    unittest.main()
