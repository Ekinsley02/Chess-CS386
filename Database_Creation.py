from connection import Connection
from connection import Config

def create_database_and_tables():
    config_dic = Config.dbinfo()
    try:
        # Temporarily use no database to create a new one
        config_dic['database'] = None
        conn = Connection(config_dic)
        conn.open_conn()

        # Create database
        create_db_query = "CREATE DATABASE IF NOT EXISTS chessData;"
        conn.get_cursor().execute(create_db_query)
        conn.close_conn()

        # Reconnect to the newly created database
        config_dic['database'] = 'chessData'
        conn = Connection(config_dic)
        conn.open_conn()

        # Create tables
        create_players_table = """
        CREATE TABLE IF NOT EXISTS Players (
            player_id INT AUTO_INCREMENT PRIMARY KEY,
            player_name VARCHAR(255) NOT NULL UNIQUE,  -- Use VARCHAR with a length instead of TEXT
            password TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
        """

        create_current_user_table = """
        CREATE TABLE IF NOT EXISTS CurrentUser (
            session_id INT AUTO_INCREMENT PRIMARY KEY,
            player_id INT NOT NULL,
            login_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (player_id) REFERENCES Players(player_id)
        );
        """

        create_games_table = """
        CREATE TABLE IF NOT EXISTS Games (
            game_id INTEGER PRIMARY KEY AUTO_INCREMENT,
            current_turn INTEGER NOT NULL,
            FOREIGN KEY (current_turn) REFERENCES Players (player_id)
        );
        """

        create_moves_table = """
        CREATE TABLE IF NOT EXISTS Moves (
            move_id INTEGER PRIMARY KEY AUTO_INCREMENT,
            game_id INTEGER NOT NULL,
            player_id INTEGER NOT NULL,
            move_count INTEGER NOT NULL DEFAULT 1,
            move_from TEXT NOT NULL,
            move_to TEXT NOT NULL,
            piece TEXT NOT NULL,
            FOREIGN KEY (game_id) REFERENCES Games (game_id),
            FOREIGN KEY (player_id) REFERENCES Players (player_id)
        );
        """

        create_current_board_table = """
        CREATE TABLE IF NOT EXISTS CurrentBoard (
            row_num INT NOT NULL,
            column_num INT NOT NULL,
            piece CHAR(1),
            PRIMARY KEY (row_num, column_num)
        );
        """


        # Execute table creation queries
        conn.get_cursor().execute(create_players_table)
        conn.get_cursor().execute(create_games_table)
        conn.get_cursor().execute(create_moves_table)
        conn.get_cursor().execute(create_current_board_table)
        conn.get_cursor().execute(create_current_user_table)

        conn.commit_changes()
        print("Database and tables created successfully!")
        conn.close_conn()

    except Exception as e:
        print(f"Error: {e}")

if __name__ == '__main__':
    create_database_and_tables()
