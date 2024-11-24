import constants

class GameState:
    def __init__(self):
        self.board = None
        self.sides = None
        self.highlights = None

        # New board information
        self.new_board = None
        self.new_sides = None
        self.new_highlights = None
        
        # Selected piece information
        self.selected_piece = None
        self.move_from = None
        self.selected_pos = None

        # Game control attributes
        self.current_player = 'P'
        self.game_condition = 0

        self.state = constants.LOGIN_MENU

    def update_board( self, board, sides, highlights ):
        
        self.board = board
        self.sides = sides
        self.highlights = highlights
    
    def reset_selection( self ):

        self.selected_piece = None
        self.move_from = None
        self.selected_pos = None
    
    def switch_player( self ):

        self.current_player = 'O' if self.current_player == 'P' else 'P'

