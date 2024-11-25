import subprocess
import threading
import queue
from mysql_util import MySQLDatabase


class ChessEngine:
    def __init__(self, executable_path, db_config):
        self.process = subprocess.Popen(
            [executable_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1
        )
        self.output_queue = queue.Queue()
        self.output_thread = threading.Thread(target=self._read_output)
        self.output_thread.daemon = True
        self.output_thread.start()

        self.db = MySQLDatabase(**db_config)
        self.db.create_database_and_tables()
        self.db.setup_database()

    def _read_output(self):
        while True:
            line = self.process.stdout.readline()
            if line == '':
                break
            self.output_queue.put(line.strip())

    def _get_output(self, expected_lines=24, include_condition=False):
        output_lines = []
        game_condition = 0

        try:
            while len(output_lines) < expected_lines:
                line = self.output_queue.get(timeout=10)
                if include_condition and line.isdigit():
                    game_condition = int(line)
                    print(f"Game Condition: {game_condition}")
                    self.db.set_game_condition(game_condition)
                    include_condition = False
                elif len(line.split()) == 8:
                    output_lines.append(line)
                else:
                    print(f"Skipped non-board line: {line}")

        except queue.Empty:
            print("Timeout while waiting for output from C program.")

        return game_condition, output_lines

    def get_initial_board(self):
        print(
            "Debug: Attempting to retrieve initial board state from the database.")
        board, sides, highlights = self.db.get_board_state()
        print("Debug: Retrieved initial board state from the database.")
        return board, sides, highlights

    def select_piece(self, row, col):
        try:
            selection_input = f'{row} {col}\n'
            print(f"Selecting piece at: {selection_input.strip()}")
            self.process.stdin.write(selection_input)
            self.process.stdin.flush()

            game_condition, first_output = self._get_output(24,
                                                            include_condition=True)
            print(f"Game Condition after selecting piece: {game_condition}")
            print(f"Board state received from C (select_piece): {first_output}")

            if len(first_output) != 24:
                print(
                    f"Incomplete board data received after selection. Expected 24 lines but got {len(first_output)} lines.")
                return game_condition, None, None, None

            board_rows = first_output[:8]
            sides_rows = first_output[8:16]
            highlights_rows = first_output[16:24]

            board = [row.split() for row in board_rows]
            sides = [row.split() for row in sides_rows]
            highlights = [row.split() for row in highlights_rows]

            print(
                f"Debug: Board, sides, highlights after selecting piece:\nBoard:\n{''.join(board_rows)}\nSides:\n{''.join(sides_rows)}\nHighlights:\n{''.join(highlights_rows)}")
            return game_condition, board, sides, highlights

        except Exception as e:
            print(f"Error selecting piece: {e}")
            return 0, None, None, None

    def move_piece(self, row, col):
        try:
            move_input = f'{row} {col}\n'
            print(f"Moving piece to ({row}, {col})")
            self.process.stdin.write(move_input)
            self.process.stdin.flush()

            game_condition, first_output = self._get_output(24,
                                                            include_condition=True)
            print(f"Game Condition after moving piece: {game_condition}")
            print(f"Board state received from C (move_piece): {first_output}")

            if len(first_output) != 24:
                print(
                    f"Incomplete board data received after move. Expected 24 lines but got {len(first_output)} lines.")
                return game_condition, None, None, None

            board_rows = first_output[:8]
            sides_rows = first_output[8:16]
            highlights_rows = first_output[16:24]

            board = [row.split() for row in board_rows]
            sides = [row.split() for row in sides_rows]
            highlights = [row.split() for row in highlights_rows]

            print(
                f"Debug: Board, sides, highlights after moving piece:\nBoard:\n{''.join(board_rows)}\nSides:\n{''.join(sides_rows)}\nHighlights:\n{''.join(highlights_rows)}")
            return game_condition, board, sides, highlights

        except Exception as e:
            print(f"Error moving piece: {e}")
            return 0, None, None, None

    def close(self):
        self.process.terminate()
        self.process.wait()
        self.db.close()
