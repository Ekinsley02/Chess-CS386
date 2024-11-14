import mysql.connector


def create_database_user():
    root_db_config = {
        'host': 'localhost',
        'user': 'root',
        'password': 'your_new_password',  # Use the new password set above
    }

    try:
        connection = mysql.connector.connect(**root_db_config)
        print("MySQL root connection established")
        cursor = connection.cursor()
        cursor.execute("CREATE DATABASE IF NOT EXISTS chess_game")
        cursor.execute(
            "CREATE USER IF NOT EXISTS 'chessplayer'@'localhost' IDENTIFIED BY '1234'")
        cursor.execute(
            "GRANT ALL PRIVILEGES ON chess_game.* TO 'chessplayer'@'localhost'")
        cursor.execute("FLUSH PRIVILEGES")
        cursor.close()
        connection.close()
        print("Database and user created successfully")
    except mysql.connector.Error as err:
        print(f"Error: {err}")


if __name__ == "__main__":
    create_database_user()
