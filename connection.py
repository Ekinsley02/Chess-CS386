import mysql.connector

class Connection:
    def __init__(self, config):
        self.config = config
        self.connection = None
        self.cursor = None

    def open_conn(self):
        try:
            self.connection = mysql.connector.connect(**self.config)
            self.cursor = self.connection.cursor()
        except mysql.connector.Error as err:
            print(f"[ERROR] Connection failed: {err}")
            raise

    def get_cursor(self):
        if not self.cursor:
            raise Exception("[ERROR] Cursor not initialized. Did you open the connection?")
        return self.cursor

    def commit_changes(self):
        if self.connection:
            self.connection.commit()

    def close_conn(self):
        if self.connection:
            self.cursor.close()
            self.connection.close()
            self.cursor = None
            self.connection = None

class Config:
    """Database configuration for connecting to MySQL."""

    HOST = '23.254.204.209'      # The IP address of your MySQL server
    DATABASE = 'chessData'       # The name of your MySQL database
    USER = 'root'                # Your MySQL username
    PASSWORD = 'Ryan123?!'       # Your MySQL password
    PORT = 3306                  # MySQL server port (default is 3306)

    CHARSET = 'utf8'             # Character set used by the database
    UNICODE = True               # Unicode settings for proper character handling

    @classmethod
    def dbinfo(cls):
        return {
            'host': cls.HOST,
            'database': cls.DATABASE,
            'user': cls.USER,
            'password': cls.PASSWORD,
            'port': cls.PORT,
            'charset': cls.CHARSET,
            'use_unicode': cls.UNICODE,
        }
############ Testing: Run: "python connection.py" to test connection #########
if __name__ == "__main__":
    config = Config.dbinfo()
    conn = Connection(config)
    try:
        conn.open_conn()
        cursor = conn.get_cursor()
        cursor.execute("SELECT DATABASE();")
        print(f"Connected to database: {cursor.fetchone()}")
    finally:
        conn.close_conn()