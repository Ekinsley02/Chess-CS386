import asyncio
import time
import pygame
from mysql_util import MySQLDatabase, create_database_user
from SubProcess import ChessEngine

# Initialize pygame
pygame.init()

# Constants Setup
WIDTH, HEIGHT = 800, 800
ROWS, COLS = 8, 8
SQUARE_SIZE = WIDTH // COLS
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BROWN = (118, 150, 86)
CREAM = (238, 238, 210)
HIGHLIGHT_COLOR = (0, 255, 0, 100)
SELECTED_COLOR = (255, 0, 0)

C_PIECE_TO_PYGAME = {
    'R': 'wr',
    'N': 'wn',
    'B': 'wb',
    'Q': 'wq',
    'K': 'wk',
    'P': 'wp',
    'r': 'br',
    'n': 'bn',
    'b': 'bb',
    'q': 'bq',
    'k': 'bk',
    'p': 'bp',
    'X': '--',
}

PIECE_IMAGES = {}
PIECE_NAMES = ['wp', 'wr', 'wn', 'wb', 'wq', 'wk', 'bp', 'br', 'bn', 'bb', 'bq',
               'bk']

for piece in PIECE_NAMES:
    try:
        PIECE_IMAGES[piece] = pygame.transform.scale(
            pygame.image.load(f'images/pieces/{piece}.png'),
            (SQUARE_SIZE, SQUARE_SIZE)
        )
    except pygame.error as e:
        print(f"Error loading image for {piece}: {e}")
        PIECE_IMAGES[piece] = None

WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Chess')

selected_piece = None
selected_pos = None


def draw_chessboard(win):
    colors = [CREAM, BROWN]
    for row in range(ROWS):
        for col in range(COLS):
            color = colors[(row + col) % 2]
            pygame.draw.rect(win, color, (
                col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))


def draw_highlights(win, highlights):
    for row in range(ROWS):
        for col in range(COLS):
            if highlights[row][col] == '1':
                highlight_surface = pygame.Surface((SQUARE_SIZE, SQUARE_SIZE),
                                                   pygame.SRCALPHA)
                highlight_surface.fill(HIGHLIGHT_COLOR)
                win.blit(highlight_surface,
                         (col * SQUARE_SIZE, row * SQUARE_SIZE))


def draw_selected(win, selected_pos):
    if selected_pos:
        row, col = selected_pos
        pygame.draw.rect(win, SELECTED_COLOR, (
            col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 3)


def draw_pieces(win, board, sides):
    for row in range(ROWS):
        for col in range(COLS):
            piece = board[row][col]
            side = sides[row][col]
            pygame_piece = '--'
            if piece == 'X':
                pygame_piece = '--'
            else:
                if side == 'P':
                    pygame_piece = C_PIECE_TO_PYGAME.get(piece.upper(), '--')
                elif side == 'O':
                    pygame_piece = C_PIECE_TO_PYGAME.get(piece.lower(), '--')
            if pygame_piece != '--':
                image = PIECE_IMAGES.get(pygame_piece)
                if image:
                    try:
                        win.blit(image, (col * SQUARE_SIZE, row * SQUARE_SIZE))
                    except Exception as e:
                        print(
                            f"Error blitting image for piece '{pygame_piece}': {e}")


def get_board_pos(x, y):
    return y // SQUARE_SIZE, x // SQUARE_SIZE


def draw_turn_indicator(win, current_player):
    font = pygame.font.Font(None, 36)
    if current_player == 'P':
        text = font.render("White's Turn", True, WHITE)
    else:
        text = font.render("Black's Turn", True, BLACK)
    win.blit(text, (10, 10))


def draw_game_condition(win, condition):
    font = pygame.font.Font(None, 48)
    if condition == 1:
        text = font.render("Checkmate! Game Over.", True, (255, 0, 0))
    elif condition == 2:
        text = font.render("Stalemate! Game Over.", True, (255, 165, 0))
    else:
        return
    text_rect = text.get_rect(center=(WIDTH // 2, HEIGHT // 2))
    win.blit(text, text_rect)
    pygame.display.update()


async def main(c_engine, db):
    clock = pygame.time.Clock()
    global selected_piece, selected_pos
    current_player = 'P'
    run = True

    # Retrieve initial board state from the database
    chess_board, chess_sides, chess_highlights = db.get_board_state()

    while run:
        clock.tick(60)
        await asyncio.sleep(0)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                row, col = get_board_pos(x, y)

                try:
                    if selected_piece:
                        game_condition, new_board, new_sides, new_highlights = c_engine.move_piece(
                            row, col)

                        if new_board and new_sides and new_highlights:
                            chess_board, chess_sides, chess_highlights = new_board, new_sides, new_highlights
                            current_player = 'O' if current_player == 'P' else 'P'

                            # Update the new state to the database
                            db.update_board_state(chess_board, chess_sides,
                                                  chess_highlights)

                        selected_piece = None
                        selected_pos = None
                    else:
                        selected_piece = chess_board[row][col]
                        selected_side = chess_sides[row][col]

                        if selected_side == current_player and selected_piece != 'X':
                            selected_pos = (row, col)
                            game_condition, new_board, new_sides, new_highlights = c_engine.select_piece(
                                row, col)

                            if new_board and new_sides and new_highlights:
                                chess_board, chess_sides, chess_highlights = new_board, new_sides, new_highlights

                                # Update the new state to the database
                                db.update_board_state(chess_board, chess_sides,
                                                      chess_highlights)
                        else:
                            selected_piece = None
                            selected_pos = None

                    # Force redraw after every move/selection
                    draw_chessboard(WIN)
                    draw_highlights(WIN, chess_highlights)
                    draw_selected(WIN, selected_pos)
                    draw_pieces(WIN, chess_board, chess_sides)
                    draw_turn_indicator(WIN, current_player)
                    pygame.display.update()

                except Exception as e:
                    print(f"An error occurred during processing: {e}")
                    selected_piece, selected_pos = None, None

        # Update display in each iteration to reflect any changes immediately
        draw_chessboard(WIN)
        draw_highlights(WIN, chess_highlights)
        draw_selected(WIN, selected_pos)
        draw_pieces(WIN, chess_board, chess_sides)
        draw_turn_indicator(WIN, current_player)
        pygame.display.update()

    pygame.quit()


if __name__ == "__main__":
    create_database_user()

    db_config = {
        'host': 'localhost',
        'user': 'chessplayer',
        'password': '1234',
        'database': 'chess_game'
    }

    c_engine = None

    try:
        c_engine = ChessEngine('./chess.exe', db_config)
        db = MySQLDatabase(**db_config)  # Initialize database connection
        asyncio.run(main(c_engine, db))
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        if c_engine:
            c_engine.close()
        if db:
            db.close()
