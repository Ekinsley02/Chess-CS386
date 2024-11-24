import json
import os
import pygame
import main
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

def get_text_input(prompt, y_offset):
    """Get text input from the user in the Pygame window."""
    font = pygame.font.Font(None, 36)
    input_rect = pygame.Rect(main.WIDTH // 2 - 100, main.HEIGHT // 2 + y_offset, 200, 40)
    color_active = (200, 200, 200)
    color_inactive = (150, 150, 150)
    color = color_inactive
    active = False
    user_text = ""

    run = True
    while run:
        main.WIN.fill(main.BROWN)
        title_text = font.render(prompt, True, main.WHITE)
        main.WIN.blit(title_text, (main.WIDTH // 2 - 100, main.HEIGHT // 2 - 100))

        # Draw input box
        pygame.draw.rect(main.WIN, color, input_rect, 2)
        text_surface = font.render(user_text, True, main.WHITE)
        main.WIN.blit(text_surface, (input_rect.x + 5, input_rect.y + 5))
        input_rect.w = max(200, text_surface.get_width() + 10)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                main.sys.exit()
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


def signup():
    """Allow the user to create a new account."""
    run = True
    while run:
        username = get_text_input("Enter Username:", -50)
        password = get_text_input("Enter Password:", 10)

        # Load credentials and check if username already exists
        credentials = load_credentials()
        if username in credentials:
            print("Username already exists. Please try again.")
            error_text = "Username already exists! Press any key to try again."
            main.WIN.fill(main.BROWN)
            error_surface = pygame.font.Font(None, 36).render(error_text, True, main.WHITE)
            main.WIN.blit(error_surface, (main.WIDTH // 2 - 150, main.HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)
        else:
            # Save new credentials
            credentials[username] = password
            save_credentials(credentials)
            print("Account created successfully!")
            success_text = "Account created successfully! Press any key to continue."
            main.WIN.fill(main.BROWN)
            success_surface = pygame.font.Font(None, 36).render(success_text, True, main.WHITE)
            main.WIN.blit(success_surface, (main.WIDTH // 2 - 200, main.HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)
            run = False


logged_in = False  # Track login status

def login():
    """Prompt the user to log in."""
    run = True
    while run:
        username = get_text_input("Enter Username:", -50)
        password = get_text_input("Enter Password:", 10)

        # Load credentials and validate login
        credentials = load_credentials()
        if username in credentials and credentials[username] == password:
            print("Login successful!")
            success_text = "Login successful! Starting game..."
            main.WIN.fill(main.BROWN)
            success_surface = pygame.font.Font(None, 36).render(success_text, True, main.WHITE)
            main.WIN.blit(success_surface, (main.WIDTH // 2 - 200, main.HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(1000)
            main.logged_in = True  # Update the global flag in main.py
            run = False
        else:
            print("Invalid username or password. Please try again.")
            error_text = "Invalid credentials! Press any key to try again."
            main.WIN.fill(main.BROWN)
            error_surface = pygame.font.Font(None, 36).render(error_text, True, main.WHITE)
            main.WIN.blit(error_surface, (main.WIDTH // 2 - 200, main.HEIGHT // 2))
            pygame.display.update()
            pygame.time.wait(2000)



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



def main_menu():
    """Display the main menu."""
    menu_run = True
    while menu_run:
        main.WIN.fill(main.BROWN)

        # Draw buttons
        login_hover = draw_button(main.WIN, "Login", main.WIDTH // 2 - 100, main.HEIGHT // 2 - 50, 200, 50, main.CREAM, main.BLACK)
        signup_hover = draw_button(main.WIN, "Sign Up", main.WIDTH // 2 - 100, main.HEIGHT // 2 + 50, 200, 50, main.CREAM, main.BLACK)

        pygame.display.update()

        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                main.sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                # Check if the login button is clicked
                if login_hover:
                    login()
                    if main.logged_in:  # Automatically go to the game upon login
                        menu_run = False
                # Check if the signup button is clicked
                elif signup_hover:
                    signup()


    main.game_state.state = main.GAME


