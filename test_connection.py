import mysql.connector


def test_connection():
    root_db_config = {
        'host': 'localhost',
        'user': 'root',
        'password': 'Tristen513',
        # Replace 'your_root_password' with the actual root password
    }

    try:
        connection = mysql.connector.connect(**root_db_config)
        if connection.is_connected():
            print("MySQL root connection established")
        connection.close()
    except mysql.connector.Error as err:
        print(f"Error: {err}")


if __name__ == "__main__":
    test_connection()
