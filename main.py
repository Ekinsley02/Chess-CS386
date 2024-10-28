# main.py

import pygame
from SubProcess import ChessEngine
import sys
import asyncio

# Initialize pygame
pygame.init()

# Define constants
WIDTH, HEIGHT = 800, 800  # Window size
ROWS, COLS = 8, 8  # Chessboard size
SQUARE_SIZE = WIDTH // COLS  # Size of each square

# RGB colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BROWN = (118, 150, 86)
CREAM = (238, 238, 210)
HIGHLIGHT_COLOR = (0, 255, 0, 100)  # Green with alpha transparency
SELECTED_COLOR = (255, 0, 0)        # Red border for selected piece

# Mapping chess piece characters from C to Pygame images
C_PIECE_TO_PYGAME = {

    'R': 'wr',  # White rook
    'G': 'wn',  # White knight
    'B': 'wb',  # White bishop
    'Q': 'wq',  # White queen
    'K': 'wk',  # White king
    'P': 'wp',  # White pawn
    'r': 'br',  # Black rook
    'g': 'bn',  # Black knight
    'b': 'bb',  # Black bishop
    'q': 'bq',  # Black queen
    'k': 'bk',  # Black king
    'p': 'bp',  # Black pawn
    'X': '--',  # Empty square
}

# Load piece images
PIECE_IMAGES = {}
PIECE_NAMES = ['wp', 'wr', 'wn', 'wb', 'wq', 'wk', 'bp', 'br', 'bn', 'bb', 'bq', 'bk']
for piece in PIECE_NAMES:
    try:
        PIECE_IMAGES[piece] = pygame.transform.scale(
            pygame.image.load(f'images/pieces/{piece}.png'),
            (SQUARE_SIZE, SQUARE_SIZE)
        )
    except pygame.error as e:
        print(f"Error loading image for {piece}: {e}")
        PIECE_IMAGES[piece] = None  # Set to None or a placeholder

# Initialize the window
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Chess')

selected_piece = None  # Track the selected piece
move_from = None  # The starting square (row, col)

# Function to draw the chessboard
def draw_chessboard(win):
    colors = [CREAM, BROWN]
    for row in range(ROWS):
        for col in range(COLS):
            color = colors[(row + col) % 2]
            pygame.draw.rect(win, color, (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

# Function to draw highlighted squares
def draw_highlights(win, highlights):
    for row in range(ROWS):
        for col in range(COLS):
            if highlights[row][col] == '1':  # Highlight flag set
                # Create a semi-transparent surface
                highlight_surface = pygame.Surface((SQUARE_SIZE, SQUARE_SIZE), pygame.SRCALPHA)
                highlight_surface.fill((0, 255, 0, 100))  # Green with alpha transparency
                win.blit(highlight_surface, (col * SQUARE_SIZE, row * SQUARE_SIZE))

# Function to draw the selected piece highlight
def draw_selected(win, selected_pos):
    if selected_pos:
        row, col = selected_pos
        # Draw a red border around the selected square
        pygame.draw.rect(win, SELECTED_COLOR,
                         (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 3)

# Function to draw the chess pieces on the board
def draw_pieces(win, board, sides):
    for row in range(ROWS):
        for col in range(COLS):
            piece = board[row][col]
            side = sides[row][col]

            if piece == 'X':  # Empty square
                pygame_piece = '--'  # No piece for an empty square
            else:
                if side == 'P':  # Player (White)
                    pygame_piece = C_PIECE_TO_PYGAME.get(piece.upper(), '--')  # Get white piece
                elif side == 'O':  # Opponent (Black)
                    pygame_piece = C_PIECE_TO_PYGAME.get(piece.lower(), '--')  # Get black piece

            if pygame_piece != '--':  # If it's not an empty square
                image = PIECE_IMAGES.get(pygame_piece)
                if image:
                    try:
                        win.blit(image, (col * SQUARE_SIZE, row * SQUARE_SIZE))
                    except Exception as e:
                        print(f"Error blitting image for piece '{pygame_piece}': {e}")
                else:
                    print(f"No image found for piece '{pygame_piece}'.")

# Function to convert pixel coordinates to board coordinates (row, col)
def get_board_pos(x, y):
    return y // SQUARE_SIZE, x // SQUARE_SIZE

# Function to display current turn
def draw_turn_indicator(win, current_player):
    font = pygame.font.Font(None, 36)
    if current_player == 'P':
        text = font.render("White's Turn", True, WHITE)
    else:
        text = font.render("Black's Turn", True, BLACK)
    win.blit(text, (10, 10))  # Display the text at the top left corner

# Function to display game condition message
def draw_game_condition(win, condition):
    font = pygame.font.Font(None, 48)
    if condition == 1:
        text = font.render("Checkmate! Game Over.", True, (255, 0, 0))
    elif condition == 2:
        text = font.render("Stalemate! Game Over.", True, (255, 165, 0))
    else:
        return  # No condition to display
    # Center the text
    text_rect = text.get_rect(center=(WIDTH // 2, HEIGHT // 2))
    win.blit(text, text_rect)
    pygame.display.update()

# Add this function to print the board state for debugging
def print_board_state(board, sides):
    print("Current Chess Board State:")
    for row in board:
        print(" ".join(row))
    print("Current Chess Sides State:")
    for row in sides:
        print(" ".join(row))

# Main game loop (with debugging added)
async def main(chess_board, chess_sides, chess_highlights, c_engine):
    clock = pygame.time.Clock()

    global selected_piece, move_from
    current_player = 'P'  # 'P' for Player (White), 'O' for Opponent (Black)
    selected_pos = None    # Position of the selected piece for highlighting

    run = True
    while run:
        clock.tick(60)  # Set the FPS

        await asyncio.sleep(0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                row, col = get_board_pos(x, y)

                if not selected_piece:  # First click (select piece)
                    selected_piece = chess_board[row][col]
                    side = chess_sides[row][col]

                    # Check if the selected piece belongs to the current player and is not empty
                    if side == current_player and selected_piece != 'X':
                        move_from = (row, col)  # Store start position
                        selected_pos = (row, col)

                        # Send the selection to C program to get highlights
                        game_condition, new_board, new_sides, new_highlights = c_engine.select_piece(row, col)
                        if game_condition in [1, 2]:
                            # Handle game end conditions
                            chess_board = new_board if new_board else chess_board
                            chess_sides = new_sides if new_sides else chess_sides
                            chess_highlights = new_highlights if new_highlights else chess_highlights
                            print_board_state(chess_board, chess_sides)  # Print updated board
                            draw_chessboard(WIN)
                            draw_highlights(WIN, chess_highlights)
                            draw_selected(WIN, selected_pos)
                            draw_pieces(WIN, chess_board, chess_sides)
                            draw_turn_indicator(WIN, current_player)
                            draw_game_condition(WIN, game_condition)
                            pygame.display.update()
                            run = False  # End the game loop
                            break

                        if new_board and new_sides and new_highlights:
                            chess_board = new_board
                            chess_sides = new_sides
                            chess_highlights = new_highlights
                            print("After selection:")
                            print_board_state(chess_board, chess_sides)  # Print updated board
                    else:
                        selected_piece = None  # Ignore if it's not the current player's piece
                        selected_pos = None
                else:  # Second click (move to destination)
                    end_row, end_col = row, col

                    # Send move to C program and get updated board
                    game_condition, new_board, new_sides, new_highlights = c_engine.move_piece(end_row, end_col)
                    if game_condition in [1, 2]:
                        # Handle game end conditions
                        chess_board = new_board if new_board else chess_board
                        chess_sides = new_sides if new_sides else chess_sides
                        chess_highlights = new_highlights if new_highlights else chess_highlights
                        print_board_state(chess_board, chess_sides)  # Print updated board
                        draw_chessboard(WIN)
                        draw_highlights(WIN, chess_highlights)
                        draw_selected(WIN, selected_pos)
                        draw_pieces(WIN, chess_board, chess_sides)
                        draw_turn_indicator(WIN, current_player)
                        draw_game_condition(WIN, game_condition)
                        pygame.display.update()
                        run = False  # End the game loop
                        break

                    if new_board and new_sides and new_highlights:
                        chess_board = new_board
                        chess_sides = new_sides
                        chess_highlights = new_highlights
                        print("After move:")
                        print_board_state(chess_board, chess_sides)  # Print updated board

                        # Switch sides after a successful move
                        current_player = 'O' if current_player == 'P' else 'P'

                    # Reset selection for the next move
                    selected_piece = None
                    move_from = None
                    selected_pos = None

        # Draw everything
        draw_chessboard(WIN)
        draw_highlights(WIN, chess_highlights)
        draw_selected(WIN, selected_pos)
        draw_pieces(WIN, chess_board, chess_sides)
        draw_turn_indicator(WIN, current_player)

        pygame.display.update()

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    c_engine = ChessEngine('./chess.exe')
    try:
        chess_board, chess_sides, chess_highlights = c_engine.get_initial_board()
        if chess_board and chess_sides and chess_highlights:
            print("Initial Chess Board:")
            for row in chess_board:
                print(" ".join(row))

            print("\nInitial Chess Sides:")
            for row in chess_sides:
                print(" ".join(row))

            print("\nInitial Chess Highlights:")
            for row in chess_highlights:
                print(" ".join(row))

            asyncio.run(main(chess_board, chess_sides, chess_highlights, c_engine))
        else:
            print("Failed to receive initial board data.")
    finally:
        c_engine.close()