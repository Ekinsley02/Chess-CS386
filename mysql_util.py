import mysql.connector


def create_database_user():
    """Function to create a database user. Adjust as needed."""
    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='root',
            password=''
        )
        cursor = connection.cursor()
        cursor.execute(
            "CREATE USER IF NOT EXISTS 'chessplayer'@'localhost' IDENTIFIED BY '1234'"
        )
        cursor.execute(
            "GRANT ALL PRIVILEGES ON chess_game.* TO 'chessplayer'@'localhost'"
        )
        cursor.execute("FLUSH PRIVILEGES")
        cursor.close()
        connection.close()
        print("Database user 'chessplayer' created and granted privileges.")
    except mysql.connector.Error as err:
        print(f"An error occurred while creating a database user: {err}")


class MySQLDatabase:
    def __init__(self, host, user, password, database):
        self.host = host
        self.user = user
        self.password = password
        self.database = database
        self.connection = self.connect()
        self.cursor = self.connection.cursor()

    def connect(self):
        try:
            connection = mysql.connector.connect(
                host=self.host,
                user=self.user,
                password=self.password,
                database=self.database
            )
            return connection
        except mysql.connector.Error as err:
            print(f"An error occurred while connecting to the database: {err}")
            return None

    def create_database_and_tables(self):
        try:
            cursor = self.connection.cursor()
            cursor.execute("CREATE DATABASE IF NOT EXISTS chess_game")
            cursor.execute("USE chess_game")
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS chess_board (
                    id INT AUTO_INCREMENT PRIMARY KEY,
                    board_row INT NOT NULL,
                    board_col INT NOT NULL,
                    piece CHAR(1),
                    side CHAR(1),
                    highlight CHAR(1),
                    game_condition INT NOT NULL DEFAULT 0
                )
            """)
            self.connection.commit()
            cursor.close()
        except mysql.connector.Error as err:
            print(
                f"An error occurred while creating database and tables: {err}")

    def setup_database(self):
        try:
            cursor = self.connection.cursor()
            cursor.execute("DELETE FROM chess_board")

            initial_board = [
                ['R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'],
                ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'],
                ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
                ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
                ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
                ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'],
                ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
                ['r', 'n', 'b', 'q', 'k', 'b', 'n', 'r']
            ]

            initial_sides = [
                ['O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'],
                ['O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'],
                ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
                ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
                ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
                ['N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'],
                ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'],
                ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P']
            ]

            for row in range(8):
                for col in range(8):
                    piece = initial_board[row][col]
                    side = initial_sides[row][col]
                    cursor.execute(
                        "INSERT INTO chess_board (board_row, board_col, piece, side) VALUES (%s, %s, %s, %s)",
                        (row, col, piece, side)
                    )

            self.connection.commit()
            cursor.close()
        except mysql.connector.Error as err:
            print(f"An error occurred: {err}")

    def get_board_state(self):
        board = [['' for _ in range(8)] for _ in range(8)]
        sides = [['' for _ in range(8)] for _ in range(8)]
        highlights = [[0 for _ in range(8)] for _ in range(8)]

        try:
            cursor = self.connection.cursor()
            cursor.execute(
                "SELECT board_row, board_col, piece, side FROM chess_board"
            )
            for board_row, board_col, piece, side in cursor.fetchall():
                board[board_row][board_col] = piece
                sides[board_row][board_col] = side
            cursor.close()
        except mysql.connector.Error as err:
            print(f"An error occurred while retrieving the board state: {err}")

        return board, sides, highlights

    def update_board_state(self, board, sides, highlights):
        try:
            cursor = self.connection.cursor()
            cursor.execute("DELETE FROM chess_board")
            for row in range(8):
                for col in range(8):
                    piece = board[row][col]
                    side = sides[row][col]
                    highlight = highlights[row][col]
                    cursor.execute(
                        "INSERT INTO chess_board (board_row, board_col, piece, side, highlight) VALUES (%s, %s, %s, %s, %s)",
                        (row, col, piece, side, highlight)
                    )
            self.connection.commit()
            cursor.close()
        except mysql.connector.Error as err:
            print(f"An error occurred while updating the board state: {err}")

    def set_game_condition(self, game_condition):
        try:
            cursor = self.connection.cursor()
            cursor.execute(
                "UPDATE chess_board SET game_condition = %s",
                (game_condition,)
            )
            self.connection.commit()
            cursor.close()
        except mysql.connector.Error as err:
            print(f"An error occurred while setting game condition: {err}")

    def close(self):
        if self.connection:
            self.connection.close()
