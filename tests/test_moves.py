import unittest
import time
from SubProcess import ChessEngine

class TestMoves(unittest.TestCase):
    def setUp(self):
        self.engine = ChessEngine("chess.exe")

    def tearDown(self):
        self.engine.close()

    def test_valid_pawn_move(self):
        print("DEBUG: Running test_valid_pawn_move...")
    
        # Step 1: Select the pawn
        game_condition, board, sides, highlights = self.engine.select_piece(6, 4)  # Select pawn at e2
    
        # Introduce a small delay to allow the subprocess to update the highlights
        time.sleep(0.5)  # Wait for 0.5 seconds

        # Fetch the highlights again
        game_condition, board, sides, highlights = self.engine.select_piece(6, 4)

        print(f"DEBUG: Highlights after selection:\n{highlights}")

        # Assertions
        self.assertEqual(game_condition, 0, "Game condition should indicate valid selection.")
        self.assertEqual(highlights[6][4], "0", "The selected piece itself should not be highlighted.")
    
        # Check the entire highlights array to see which positions are highlighted
        highlighted_positions = []
        for row_index, row in enumerate(highlights):
            for col_index, value in enumerate(row):
                if value == "1":
                    highlighted_positions.append((row_index, col_index))

        print(f"DEBUG: Highlighted positions: {highlighted_positions}")
    
        # Check valid moves for the pawn (e2 -> e3 and e4)
        self.assertEqual(highlights[5][4], "1", "e3 should be highlighted as a valid move.")  # Row 5 is e3

    def test_invalid_move(self):
        print("DEBUG: Running test_invalid_move...")

        # Step 1: Select the piece
        game_condition, board, sides, highlights = self.engine.select_piece(6, 4)  # Select pawn at e2

        # Introduce a delay to allow the C engine to update
        time.sleep(0.5)

        # Attempt to move the piece to an invalid position (2, 4)
        game_condition, board, sides, highlights = self.engine.move_piece(2, 4)
        
        # Assertions
        self.assertNotEqual(game_condition, 0, "Game condition should indicate invalid move.")

if __name__ == "__main__":
    unittest.main()
