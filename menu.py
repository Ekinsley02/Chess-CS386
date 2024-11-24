import json
import os
import pygame
import sys  # Added to use sys.exit()

# JSON file to store user credentials
CREDENTIALS_FILE = "user_data.json"

# Initialize the credentials file if it doesn't exist
if not os.path.exists(CREDENTIALS_FILE):
    with open(CREDENTIALS_FILE, "w") as file:
        json.dump({}, file)

def load_credentials():
    """Load user credentials from the JSON file."""
    with open(CREDENTIALS_FILE, "r") as file:
        return json.load(file)

def save_credentials(credentials):
    """Save user credentials to the JSON file."""
    with open(CREDENTIALS_FILE, "w") as file:
        json.dump(credentials, file)

def get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, prompt, y_offset):
    """Get text input from the user in the Pygame window."""
    font = pygame.font.Font(None, 36)
    input_rect = pygame.Rect(WIDTH // 2 - 100, HEIGHT // 2 + y_offset, 200, 40)
    color_active = (200, 200, 200)
    color_inactive = (150, 150, 150)
    color = color_inactive
    active = False
    user_text = ""

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

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
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
        password = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Password:", 10)

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

def login(WIN, WIDTH, HEIGHT, BROWN, WHITE, game_state, logged_in):
    """Prompt the user to log in."""
    run = True
    while run:
        username = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Username:", -50)
        password = get_text_input(WIN, WIDTH, HEIGHT, BROWN, WHITE, "Enter Password:", 10)

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
    return logged_in

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
                    logged_in = login(WIN, WIDTH, HEIGHT, BROWN, WHITE, game_state, logged_in)
                    if logged_in:
                        print("Login successful! Transitioning to MENU...")  # Debug
                        game_state.state = 'MENU'  # Set the state to MENU
                        menu_run = False
                elif signup_hover:
                    signup(WIN, WIDTH, HEIGHT, BROWN, WHITE)

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
