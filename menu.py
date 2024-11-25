#import json

import os
import pygame
import sys  # Added to use sys.exit()

### Added Libraries - SQL ###
from connection import Connection
from connection import Config
#############################

################### commented JSON code ##################
# JSON file to store user credentials
#CREDENTIALS_FILE = "user_data.json"

# Initialize the credentials file if it doesn't exist
# if not os.path.exists(CREDENTIALS_FILE):
#     with open(CREDENTIALS_FILE, "w") as file:
#         json.dump({}, file)

# def load_credentials():
#     """Load user credentials from the JSON file."""
#     with open(CREDENTIALS_FILE, "r") as file:
#         return json.load(file)

# def save_credentials(credentials):
#     """Save user credentials to the JSON file."""
#     with open(CREDENTIALS_FILE, "w") as file:
#         json.dump(credentials, file)
###### END OF commented JSON code       ##################





################### Begining of User SQL Implementation ###################
def load_credentials():
    # Load user credentials from the database #
    print("[DEBUG] Starting to load credentials from the database.")  # Debug
    config_dic = Config.dbinfo()
    connection = Connection(config_dic)

    try:
        print("[DEBUG] Opening database connection...")  # Debug
        connection.open_conn()
        cursor = connection.get_cursor()
        print("[DEBUG] Database connection opened successfully.")  # Debug

        # Fetch all players from the Players table
        print("[DEBUG] Executing query to fetch player credentials.")  # Debug
        cursor.execute("SELECT player_name, password FROM Players")
        result = cursor.fetchall()
        print(f"[DEBUG] Query executed successfully. Retrieved {len(result)} players.")  # Debug

        # Convert the result into a dictionary
        credentials = {row[0]: row[1] for row in result}
        print(f"[DEBUG] Converted database results into a dictionary: {credentials}")  # Debug
        return credentials

    except Exception as e:
        print(f"[ERROR] Could not load credentials: {e}")  # Debug
        return {}

    finally:
        print("[DEBUG] Closing database connection...")  # Debug
        connection.close_conn()
        print("[DEBUG] Database connection closed.")  # Debug


#### Save User Credentials to Current_User Table
def save_credentials(credentials):
    """
    Save user credentials to the database.

    :param credentials: A dictionary with username-password pairs.
    """
    print("[DEBUG] Starting to save credentials to the database.")  # Debug
    config_dic = Config.dbinfo()
    connection = Connection(config_dic)

    try:
        print("[DEBUG] Opening database connection...")  # Debug
        connection.open_conn()
        cursor = connection.get_cursor()
        print("[DEBUG] Database connection opened successfully.")  # Debug

        # Insert each username-password pair into the Players table
        for username, password in credentials.items():
            print(f"[DEBUG] Attempting to save credentials for user: {username}")  # Debug
            try:
                cursor.execute(
                    "INSERT INTO Players (player_name, password) VALUES (%s, %s)",
                    (username, password)
                )
                print(f"[DEBUG] Credentials for user '{username}' saved successfully.")  # Debug
            except Exception as e:
                print(f"[WARNING] Could not save credentials for {username}: {e}")  # Debug

        print("[DEBUG] Committing changes to the database.")  # Debug
        connection.commit_changes()
        print("[DEBUG] All credentials saved successfully.")  # Debug

    except Exception as e:
        print(f"[ERROR] Could not save credentials: {e}")  # Debug

    finally:
        print("[DEBUG] Closing database connection...")  # Debug
        connection.close_conn()
        print("[DEBUG] Database connection closed.")  # Debug

###################   END of User SQL Implementation    ###################


def get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, prompt, y_offset):
    """Get text input from the user in the Pygame window."""
    font = pygame.font.Font(None, 36)
    input_rect = pygame.Rect(WIDTH // 2 - 100, HEIGHT // 2 + y_offset, 200, 40)
    color_active = (200, 200, 200)
    color_inactive = (150, 150, 150)
    color = color_inactive
    active = False
    user_text = ""

    back_button_rect = pygame.Rect(50, 50, 100, 40)  # Position and size of the "Back" button

    run = True
    while run:
        WIN.fill(BROWN)
        title_text = font.render(prompt, True, WHITE)
        WIN.blit(title_text, (WIDTH // 2 - 100, HEIGHT // 2 - 100))

        # Draw input box
        pygame.draw.rect(WIN, color, input_rect, 2)
        text_surface = font.render(user_text, True, WHITE)
        WIN.blit(text_surface, (input_rect.x + 5, input_rect.y + 5))
        input_rect.w = max(200, text_surface.get_width() + 10)

        # Draw the "Back" button
        pygame.draw.rect(WIN, (200, 0, 0), back_button_rect)  # Red color for "Back" button
        back_text = font.render("Back", True, WHITE)
        back_text_rect = back_text.get_rect(center=back_button_rect.center)
        WIN.blit(back_text, back_text_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if back_button_rect.collidepoint(event.pos):
                    return None  # Return None to indicate "Back" was clicked
                # Toggle active state if clicked inside the input box
                if input_rect.collidepoint(event.pos):
                    active = not active
                else:
                    active = False
                color = color_active if active else color_inactive
            if event.type == pygame.KEYDOWN:
                if active:
                    if event.key == pygame.K_RETURN:
                        run = False  # End input on Enter
                    elif event.key == pygame.K_BACKSPACE:
                        user_text = user_text[:-1]
                    else:
                        user_text += event.unicode

    return user_text

def signup(WIN, WIDTH, HEIGHT, BROWN, WHITE):
    """Allow the user to create a new account."""
    run = True
    while run:
        username = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Username:", -50)
        if username is None:
            # User clicked "Back"
            return False  # Return False to indicate to go back

        password = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Password:", 10)
        if password is None:
            # User clicked "Back"
            return False  # Return False to indicate to go back

        # Load credentials and check if username already exists
        credentials = load_credentials()
        if username in credentials:
            print("Username already exists. Please try again.")
            error_text = "Username already exists! Press any key to try again."
            WIN.fill(BROWN)
            error_surface = pygame.font.Font(None, 36).render(error_text, True, WHITE)
            WIN.blit(error_surface, (WIDTH // 2 - 150, HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)
        else:
            # Save new credentials
            credentials[username] = password
            save_credentials(credentials)
            print("Account created successfully!")
            success_text = "Account created successfully! Press any key to continue."
            WIN.fill(BROWN)
            success_surface = pygame.font.Font(None, 36).render(success_text, True, WHITE)
            WIN.blit(success_surface, (WIDTH // 2 - 200, HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)
            run = False
    return True  # Return True to indicate signup completed

def login(WIN, WIDTH, HEIGHT, BROWN, WHITE, game_state, logged_in):
    """Prompt the user to log in."""
    run = True
    while run:
        username = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Username:", -50)
        if username is None:
            # User clicked "Back"
            return logged_in, False  # Return logged_in and False to indicate to go back

        password = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Password:", 10)
        if password is None:
            # User clicked "Back"
            return logged_in, False  # Return logged_in and False to indicate to go back

        # Load credentials and validate login
        credentials = load_credentials()
        if username in credentials and credentials[username] == password:
            print("Login successful!")
            success_text = "Login successful! Starting game..."
            WIN.fill(BROWN)
            success_surface = pygame.font.Font(None, 36).render(success_text, True, WHITE)
            WIN.blit(success_surface, (WIDTH // 2 - 200, HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(1000)
            logged_in = True  # Update the login status
            run = False
        else:
            print("Invalid username or password. Please try again.")
            error_text = "Invalid credentials! Press any key to try again."
            WIN.fill(BROWN)
            error_surface = pygame.font.Font(None, 36).render(error_text, True, WHITE)
            WIN.blit(error_surface, (WIDTH // 2 - 200, HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)
    return logged_in, True  # Return logged_in and True to continue

def draw_button(win, text, x, y, width, height, color, text_color):
    """Draw a button and return True if clicked."""
    font = pygame.font.Font(None, 36)
    button_rect = pygame.Rect(x, y, width, height)

    # Draw the button
    pygame.draw.rect(win, color, button_rect)
    pygame.draw.rect(win, (0, 0, 0), button_rect, 2)  # Add a border
    text_surface = font.render(text, True, text_color)
    text_rect = text_surface.get_rect(center=(x + width // 2, y + height // 2))
    win.blit(text_surface, text_rect)

    # Check for mouse position and click
    mouse_pos = pygame.mouse.get_pos()
    if button_rect.collidepoint(mouse_pos):
        pygame.draw.rect(win, (200, 200, 200), button_rect)  # Highlight on hover
        win.blit(text_surface, text_rect)
        return True  # Indicate hover for external processing
    return False

def login_menu(WIN, WIDTH, HEIGHT, BROWN, CREAM, BLACK, WHITE, game_state, logged_in):
    """Display the login menu."""
    menu_run = True
    while menu_run:
        WIN.fill(BROWN)

        # Draw buttons
        login_hover = draw_button(WIN, "Login", WIDTH // 2 - 100, HEIGHT // 2 - 50, 200, 50, CREAM, BLACK)
        signup_hover = draw_button(WIN, "Sign Up", WIDTH // 2 - 100, HEIGHT // 2 + 50, 200, 50, CREAM, BLACK)

        pygame.display.update()

        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if login_hover:
                    logged_in, continue_to_menu = login(WIN, WIDTH, HEIGHT, BROWN, WHITE, game_state, logged_in)
                    if logged_in and continue_to_menu:
                        print("Login successful! Transitioning to MENU...")  # Debug
                        game_state.state = 'MENU'  # Set the state to MENU
                        menu_run = False
                    elif not continue_to_menu:
                        # User clicked "Back" in login; stay in login menu
                        pass
                elif signup_hover:
                    signup_completed = signup(WIN, WIDTH, HEIGHT, BROWN, WHITE)
                    if not signup_completed:
                        # User clicked "Back" in signup; stay in login menu
                        pass
        # We don't need to return logged_in here, as it's updated in place
    print("Exiting Login Menu...")  # Debug
    return logged_in  # Return the updated logged_in status

def main_menu(WIN, WIDTH, HEIGHT, BROWN, CREAM, BLACK, WHITE, game_state):
    """Display the main menu."""
    print("Main Menu Active...")  # Debug
    menu_run = True

    while menu_run:
        WIN.fill(BROWN)

        # Draw buttons
        pass_play_hover = draw_button(WIN, "Pass and Play", WIDTH // 2 - 100, HEIGHT // 2 - 100, 200, 50, CREAM, BLACK)
        teacher_ai_hover = draw_button(WIN, "TeacherAI", WIDTH // 2 - 100, HEIGHT // 2, 200, 50, CREAM, BLACK)
        online_play_hover = draw_button(WIN, "Online Play", WIDTH // 2 - 100, HEIGHT // 2 + 100, 200, 50, CREAM, BLACK)

        pygame.display.update()

        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if pass_play_hover:
                    print("Pass and Play Selected! Transitioning to GAME...")  # Debug
                    game_state.state = 'GAME'  # Transition to GAME state
                    menu_run = False  # Exit the main menu loop
                elif teacher_ai_hover or online_play_hover:
                    print("Coming Soon Alert Triggered!")  # Debug
                    WIN.fill(BROWN)
                    alert_text = "Coming Soon!"
                    alert_surface = pygame.font.Font(None, 36).render(alert_text, True, WHITE)
                    WIN.blit(alert_surface, (WIDTH // 2 - 100, HEIGHT // 2))
                    pygame.display.update()
                    pygame.time.wait(2000)
