from connection import Connection
from connection import Config

def save_current_board(game_state):
    """
    Save the current board state from a GameState instance to the `CurrentBoard` table.
    :param game_state: An instance of GameState
    """
    #print("[DEBUG] Entering save_current_board function.")

    # Check if the board exists in the game state
    if not game_state.board:
        print("[ERROR] The board is empty or not initialized.")
        return

    print("[DEBUG] Board state exists. Preparing to save to database...")
    print("[DEBUG] Current board state:")
    for row in game_state.board:
        print(" ".join(row))

    # Fetch database configuration and initialize connection
    config_dic = Config.dbinfo()
    print("[DEBUG] Database configuration retrieved:", config_dic)

    connection = Connection(config_dic)

    try:
        print("[DEBUG] Opening database connection...")
        connection.open_conn()
        cursor = connection.get_cursor()
        print("[DEBUG] Database connection opened successfully.")

        # Clear the existing data in the CurrentBoard table
        print("[DEBUG] Clearing existing data in the CurrentBoard table...")
        cursor.execute("DELETE FROM CurrentBoard;")
        print("[DEBUG] Existing data cleared.")

        # Populate the table with the current board state
        print("[DEBUG] Inserting new board state into CurrentBoard table...")
        for row_num, row in enumerate(game_state.board, start=1):
            for col_num, piece in enumerate(row, start=1):
                #print(f"[DEBUG] Inserting: row_num={row_num}, col_num={col_num}, piece='{piece}'")
                cursor.execute(
                    "INSERT INTO CurrentBoard (row_num, column_num, piece) VALUES (%s, %s, %s);",
                    (row_num, col_num, piece)
                )

        # Commit the changes
        print("[DEBUG] Committing changes to the database...")
        connection.commit_changes()
        print("[DEBUG] Current board saved to the database successfully!")
    except Exception as e:
        print(f"[ERROR] An error occurred while saving the current board: {e}")
    finally:
        print("[DEBUG] Closing the database connection...")
        connection.close_conn()
        print("[DEBUG] Database connection closed.")
