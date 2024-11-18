# main.py
import pygame
from SubProcess import ChessEngine
import sys
import asyncio
import time
from GameState import GameState

# Initialize pygame
pygame.init()

# Define constants

# Window size
WIDTH, HEIGHT = 800, 800

# Row and col size
ROWS, COLS = 8, 8 

# Size of each square
SQUARE_SIZE = WIDTH // COLS

# RGB colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BROWN = (118, 150, 86)
CREAM = (238, 238, 210)

# Transparent green backround
HIGHLIGHT_COLOR = (0, 255, 0, 100)

# Red borer for selected piece
SELECTED_COLOR = (255, 0, 0)

# Remap chess pieces from C program
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

# traverse piece names array
for piece in PIECE_NAMES:

    #try to assign each piece to coresponing piece image
    try:
        PIECE_IMAGES[ piece ] = pygame.transform.scale(
            pygame.image.load( f'images/pieces/{ piece }.png' ),
                ( SQUARE_SIZE, SQUARE_SIZE )
        )

    except pygame.error as e:
        print( f"Error loading image for { piece }: { e }" )
        PIECE_IMAGES[ piece ] = None

# Initialize the window based on width and height pixel count
WIN = pygame.display.set_mode( ( WIDTH, HEIGHT ) )

# set the window caption to chess
pygame.display.set_caption('Chess')

game_state = GameState()

# Function name: draw_chessboard
# Process: creates a board of squares for rows and columns (8 for both)
#  make each square oposite colors using modulo 2
#  rectify (draw) each of these pieces to the board
# Input: current window
# Output: a drawn chessboard
# Dependencies: rect
def draw_chessboard(win):

    #initialize each color in array to alternate
    colors = [ CREAM, BROWN ]

    # for loop to make a chessboard
    for row in range( ROWS ):

        for col in range( COLS ):

            color = colors[ ( row + col ) % 2 ]
            pygame.draw.rect( win, color, ( col * SQUARE_SIZE,
                             row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE ) )

# Function name: draw_highlights
# Process: goes over each highlight in 2d array, if the highlight is 1 (true)
# highlight the current square with transparent green
# Input: current window, highlighting array
# Output: a highlighted chessboard
# Dependencies: fill, blit
def draw_highlights(win, highlights):

    for row in range( ROWS ):

        for col in range( COLS ):

            # check if the board at current index is true for highlighting
            if highlights[row][col] == '1': 

                # define surface to fill ( current square )
                highlight_surface = pygame.Surface( ( SQUARE_SIZE, SQUARE_SIZE ),
                                                                     pygame.SRCALPHA )
                
                # fill the current square with transparent green
                highlight_surface.fill( ( 0, 255, 0, 100 ) )

                # blit (basically another draw but for image ) green surface onto square position
                win.blit(highlight_surface, (col * SQUARE_SIZE, row * SQUARE_SIZE))

# Function name: draw_selected
# Process: at the slected position, the current square will turn red
#  for selecting a piece before moving
# Input: current window, selected piece position
# Output: a red square around the selected piece
# Dependencies: rect
def draw_selected(win, selected_pos):

    # check if valid selected position
    if selected_pos:

        # if true, assign the row and col to selected_position
        row, col = selected_pos

        # draw a red border around the selected square
        pygame.draw.rect( win, SELECTED_COLOR,
                         ( col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE), 3)

# Function name: draw_pieces
# Process: draw each piece on the current board
# Input: current window, piece board, side board
# Output: every piece and adjacent side of the current board
# ( overlaps ontop of plane board with no pieces )
# Dependencies: get, blit
def draw_pieces(win, board, sides):

    # traverse all conditional boards ( piece, sides )
    for row in range(ROWS):

        for col in range(COLS):

            # assign the current piece
            piece = board[ row ][ col ]

            # assign the current side
            side = sides[ row ][ col ]

            # check if the current square is empty
            if piece == 'X':
                pygame_piece = '--'  # No piece for an empty square
            else:

                # check if the current side is white
                if side == 'P':
                    
                    # get the current white piece
                    pygame_piece = C_PIECE_TO_PYGAME.get( piece.upper(), '--' )

                # check if the current side is black
                elif side == 'O':

                    # get the current black piece
                    pygame_piece = C_PIECE_TO_PYGAME.get( piece.lower(), '--' )

            # if the current piece is not empty
            if pygame_piece != '--':
                
                # get the current piece image
                image = PIECE_IMAGES.get( pygame_piece )

                # if getting the image was a success
                if image:

                    # try to draw the image to the screen
                    try:
                        win.blit(image, ( col * SQUARE_SIZE, row * SQUARE_SIZE ) )

                    # otherwise throw an exception for not drawing
                    except Exception as e:
                        print( f"Error blitting image for piece '{ pygame_piece }': { e }" )

                # otherwise, no image found and report
                else:
                    print( f"No image found for piece '{ pygame_piece }'." )

# Function name: get_board_pos
# Process: converts the x and y pixel to the selected board position
# this was redone so that the squares are more alligned.
# Input: x pixel cordinate, y pixel cordinate
# Output: every piece and adjacent side of the current board
# ( overlaps ontop of plane board with no pieces )
# Dependencies: NONE
def get_board_pos( x, y ):
    return y // SQUARE_SIZE, x // SQUARE_SIZE

# Function name: drawn_turn_indicator
# Process: check for the current turn, displays the side
# at the top right of the window
# Input: current window, current side
# Output: side indicator at the top left of window
# Dependencies: blit
def draw_turn_indicator( win ):

    # initialize font for text
    font = pygame.font.Font( None, 36 )

    # check if the current side is white
    if game_state.current_player == 'P':

        # render the text with given font
        text = font.render( "White's Turn", True, WHITE )

    # otherwise do the same for black
    else:
        text = font.render( "Black's Turn", True, BLACK )

    # draw the text at the top left of window (10 pixels in)
    win.blit(text, (10, 10))

# Function name: draw_game_condition
# Process: checks the current condition,
# if the current condition is 0, then game still in progress
# if it is 1, then checkmate
# if it is 2, then stalemate
# displays texts at the center
# Input: current window, win conditon
# Output: win condition in the middle of screen
# Dependencies: render, blit, update
def draw_game_condition( win, condition ):

    # initilaize font and font size
    font = pygame.font.Font(None, 48)

    # check/set for checkmate
    if condition == 1:
        text = font.render( "Checkmate! Game Over.", True, ( 255, 0, 0 ) )

    # check/set for stalemate
    elif condition == 2:
        text = font.render( "Stalemate! Game Over.", True, ( 255, 165, 0 ) )

    # otherwise, nothing to output
    else:
        return
    
    # center the text
    text_rect = text.get_rect( center = ( WIDTH // 2, HEIGHT // 2 ) )

    # draw the text in the middle
    win.blit( text, text_rect )

    # update imeditely to change screen
    pygame.display.update()

# Function name: print_board_state
# Process: prints the current board state to terminal (for debug)
# Input: current piece board, current sides board
# Output: board conditions to terminal
# Dependencies: print
def print_board_state( board, sides ):

    print("Current Chess Board State:")
    for row in board:

        print( " ".join( row ) )

    print("Current Chess Sides State:")
    for row in sides:
        
        print( " ".join( row ) )

# Function name: boards_are_equal
# Process: Test if the two boards given are equal, reports if true
# Input: two boards to compare
# Output: comparison of boards
# Dependencies: NONE
def boards_are_equal(board1, board2):

    if len(board1) != len(board2):
        return False
    
    for row1, row2 in zip(board1, board2):
        if row1 != row2:
            return False
        
    return True

# Function name: main (with debug added)
# Process: creates a main game loop and handles events accordingly
# Input: pieces, sides, and highlight board states (2D arrays), c_engine (subproccess)
# Output: board conditions to terminal
# Dependencies: print
async def main( c_engine ):

    # create a clock for framerate
    clock = pygame.time.Clock()

    # initilaize local variables
    run = True

    # this is the main game loop to handle conditions
    while run:

        # set FPS to 60
        clock.tick( 60 )

        # unknown if we need this at this time
        await asyncio.sleep(0)

        # check for each event
        for event in pygame.event.get():

            # if the X is pressed in the window, quit
            if event.type == pygame.QUIT:

                run = False

            # **Check for game over condition immediately**
            if game_state.game_condition in [1, 2]:
                # Handle game over conditions
                game_state.board = game_state.new_board if game_state.new_board else game_state.board
                game_state.sides = game_state.new_sides if game_state.new_sides else game_state.sides
                game_state.highlights = game_state.new_highlights if game_state.new_highlights else game_state.highlights
                
                print_board_state(game_state.board, game_state.sides)
                draw_chessboard(WIN)
                draw_highlights(WIN, game_state.highlights)
                draw_selected(WIN, game_state.selected_pos)
                draw_pieces(WIN, game_state.board, game_state.sides)
                draw_turn_indicator(WIN)
                draw_game_condition(WIN, game_state.game_condition)
                
                pygame.display.update()
                await asyncio.sleep(3)
                run = False  # End the game loop
                break  # Exit the event handling loop

            # check for mouseclick
            if event.type == pygame.MOUSEBUTTONDOWN:

                # determine mouseclick cordinates (in pixels)
                x, y = event.pos

                # get the board positon (indexes) from the pixels
                row, col = get_board_pos(x, y)

                # check to see if this is the first click (selecting)
                if not game_state.selected_piece:

                    # get the current piece type
                    game_state.selected_piece = game_state.board[ row ][ col ]
                    
                    # get the current piece side (either (O)ponent, (P)layer)
                    game_state.sides = game_state.sides[ row ][ col ]

                    # check to see if the selected side is current player
                        # and not empty (no pieces)
                    if game_state.sides == game_state.current_player and game_state.selected_piece != 'X':
                        
                        # keep track of initial position
                        game_state.move_from = ( row, col )

                        # asssign the selected position
                        game_state.selected_pos = (row, col)

                        # Send the selection to C program to get highlights
                        game_state.game_condition, game_state.board, game_state.sides, game_state.highlights = c_engine.select_piece( row, col )
                        
                        # check to see if there is new information
                        if game_state.new_board and game_state.new_sides and game_state.new_highlights:

                            # make the conditional boards equal the updated board
                            game_state.update_board( game_state.board, game_state.sides, game_state.highlights )

                            # this is for debugging shows the board after selection
                            print( "After selection:" )
                            print_board_state( game_state.board, game_state.sides )

                    # otherwise ignore since its not the players piece
                    else:
                        game_state.selected_piece = None
                        game_state.selected_pos = None

                # otherwise, its in the moving state (post selecting)
                else:
                    # assign the end row/col (where the user selected)
                    end_row, end_col = row, col 

                    # move the pieces using chess engine, capture pieces, highlights, and sides
                    game_state.game_condition, game_state.new_board, game_state.new_sides, game_state.new_highlights = c_engine.move_piece(end_row, end_col)

                    # Check if the move was valid by comparing boards
                    if game_state.new_board and not boards_are_equal(game_state.new_board, game_state.board):
                        # Move was valid, update the boards in game_state
                        game_state.update_board(game_state.new_board, game_state.new_sides, game_state.new_highlights)

                        print("After move:")
                        print_board_state(game_state.board, game_state.sides)

                        # Switch to the other player
                        game_state.switch_player()

                    else:
                        # Move was invalid, allow the player to try again without resetting selection
                        print("Invalid move. Please try again.")

                    # Reset selection for the next move
                    game_state.selected_piece = None
                    game_state.move_from = None
                    game_state.selected_pos = None

        # Draw everything
        draw_chessboard( WIN )
        draw_highlights( WIN, game_state.highlights )
        draw_selected( WIN, game_state.selected_pos )
        draw_pieces( WIN, game_state.board, game_state.sides )
        draw_turn_indicator( WIN )

        pygame.display.update()

    pygame.quit()
    sys.exit()

# this defines the main, so that no other functions are ran initially
if __name__ == "__main__":
    c_engine = ChessEngine('./chess.exe')

    # if the proper information is uploaded, display it to terminal (for debug)
    try:
        game_state.board, game_state.sides, game_state.highlights = c_engine.get_initial_board()
        if game_state.board and game_state.sides and game_state.highlights:
            print("Initial Chess Board:")
            for row in game_state.board:
                print(" ".join(row))

            print("\nInitial Chess Sides:")
            for row in game_state.sides:
                print(" ".join(row))

            print("\nInitial Chess Highlights:")
            for row in game_state.highlights:
                print(" ".join(row))

            asyncio.run(main(c_engine))
        else:
            print("Failed to receive initial board data.")
    
    # lastly close the c engine
    finally:
        c_engine.close()