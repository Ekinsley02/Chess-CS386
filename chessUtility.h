#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

/*
*********************************
LOG:
Notes for next session:
rook hasn't been implemented yet,
 I stopped at check rook valid posiiton. 
Remember that the check valid position is for PASSIVE,
 but may be used for BATTLE


 current task:
 merge check battle position and valid position

 NOTE:
 stopped at fault segment for going left with rook
 also pawn on far left does whack stuff

 pawn still moves foward even if there is another piece there in attack <- fixed but a little redundant, used flags to control check battle, needs oponents side fixed

 I think I am ready to move onto rook, pawn should only highlight individual sides when attacking instead of both -1 and +1


.......
Currently lots of redundancy, you can reduce the number of lines of by merging checking which side is which and just do it in switch statements
also check pawn position for oponent needs to be implemented
I stopped at rook highlighting, make it so it highlights the first enemy - FIXED by making highlight struct member

.......
Still lots of redundancy, fix when back home
I stopped at adding logic for pawn and rook for the opponents side.

.......
I left off on trying to highight the knights position, probably have to use pointers
I also created determineOppositeSide function to try to start fixing the redundancy

right now I am trying to fix highlight complexity by making a struct member called highlight,
this is so the original pieces type remains the same.

.......
highlight struct member successfully added
redundancy mostly taken care of, still some in check battle/valid positions
pawn battle dehighlight is funky

.......
I just integrated switching sides here is what I noticed:
- if wrong input still switches sides - FIXED
- rook highlight goes past the first enemy but the attack doesn't - FIXED
- pawn attack doesn't work when oponents pieces are moved from initial positions - REWORKING

.......
Trying to rework my check position functions so I don't have to have two seperate passive and battle functions, everything integrates nicely except for pawn, furthur investigtion needed.
 current issues after rework
 segmentation error for rook when selected ( of course ) - FIXED
 side pawns don't attack for opponent - FIXED
 bishop doesn't highlight - FIXED
reduncancy of check battle positions fixed
ready to start making check king positions, after that start working on check, stalemate, and castling logic
also movePiece function may be redundant

........ 
started integrating putInCheck function, which doesn't allow the player to put king into check, I have the logic and the output says you can't move there but the piece does still get moved

........
stopped at trying to do putInCheck for bishop, also I think the putInCheck function isn't allowing the opponent to put the king in check

........
just successfullly implemented checkmate logic, heavily redundant so I need to think about how to optimize.
Need to test it for bugs, also my boards rows are backwards, should be 8-1 not 1-8.
Also need to make check logic for knight DONE
make a clearBoard function
checkmate for opponent is whack - FIXED

........
checkmate finished, all I need to do now is checkmate for starting pawns, make input only read char or int, optomize checkmate, optomize castling and GUR then I am done!

*********************************
*/

// inlcuded libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


// constants
#define BOARD_SIZE 8
#define PAWN 'P'
#define BISHOP 'B'
#define KNIGHT 'G'
#define ROOK 'R'
#define QUEEN 'Q'
#define KING 'K'
#define NON_PLAYER 'X'
#define HIGHLIGHT 'H'
#define DEHIGHLIGHT 'D'

// check code constants
#define INCHECK 'I'
#define PUTCHECK 'Z'

// colors for text 
#define RED_TEXT "\x1b[31m"
#define BLUE_TEXT "\x1b[34m"
#define GREEN_TEXT "\x1b[32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\x1b[0m"

// different conditional flags
#define MOVING -2
#define SELECTING -1
#define PASSIVE 0
#define BATTLE 1
#define BOTH 3
#define CHECK 4
#define STALEMATE 4

// create an empty flag
#define NONE -3

typedef struct ChessBoardStruct
   {
    char type;
    char side;
    bool highlight;
    bool hasMoved;
    bool castlePos;
   } ChessBoardType;



// function prototypes

/*
Description: checks all valid positions for the rook
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkIfAllValidBishopPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int checkRowIndex, int checkColIndex, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode );

/*
Description: checks all valid positions for the rook
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidKingPositions( ChessBoardType **board, ChessBoardType **checkedBoard, char currentTurn, char currentType, int currentState, int initialRow, int initialCol );

/*
Description: checks all valid positions for the knight
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidKnightPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode );

/*
Description: checks if the current piece is on the leftmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidPawnPositions( ChessBoardType **board, ChessBoardType **checkedBoard, char currentTurn, char currentType, int currentState, int initialRow, int initialCol, int currentCode );

/*
Description: Checks every posible piece 
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidRookPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int checkRowIndex, int checkColIndex, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode );

/*
Description: checks if the current piece is on the leftmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkEdgePieceLeft( ChessBoardType **board, int currentCol );

/*
Description: checks if the current piece is on the rightmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkEdgePieceRight( ChessBoardType **board, int currentCol );

/*
Description: compares every viable rook position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/
bool checkBishopPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState );

/*
Description: checks if the given position is in view for battle
and checks if the current piece has no obstructions.
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/

// previously check battle position
bool checkIfValidPosition( ChessBoardType **board, char currentType,
                           char currentTurn, int initialRow, int initialCol, int currentRow, int currentCol, int *currentState, bool initialPawn );

/*
Description: checks available positions for king, only moves king if it doesn't put it in check
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/
bool checkKingPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState );

/*
Description: compares every viable knight position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/
bool checkKnightPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState );

/*
Description: compares every viable pawn position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/
bool checkPawnPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState, bool initialPawn );

/*
Description: compares every viable rook position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/
bool checkRookPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState );

/*
Description: converts the players column input to an index
Input: players chosen column
Output: the index from the given column
Dependancies: NONE
*/
int columnToIndex( char chosenCol );

/*
Description: Copies the current board to another board, used for looking into the next move
Input: destination board, source board
Output: copied board from source
Dependancies: NONE
*/
void copyBoard( ChessBoardType **destinationBoard, ChessBoardType **sourceBoard );

/*
Description: determines the opposite side guven the current side
Input: currentTurn
Output: The opposite of the current side
Dependancies: NONE
*/
char determineOppositeSide( char currentTurn );

/*
Description: determines the sides of the pieces on initial board
Input: Chessboard
Output: The pieces on the board sides identified
Dependancies: NONE
*/
void determineSides( ChessBoardType **board );

/*
Description: finds the piece type of the given board row and column
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
char determineType( ChessBoardType **board, int boardRow, int boardCol );

/*
Description: prints the bottom half of the board, after the pieces.
Input: NONE
Output: printed lower chess board
Dependancies: NONE
*/
void displayBottomBoard();

/*
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: NONE
*/
void displayChessBoard( ChessBoardType **board, int rows, int cols );

/*
Description: prints the upper half of the board, before the pieces.
Input: NONE
Output: printed upper chess board
Dependancies: NONE
*/
void displayTopBoard();

/*
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: NONE
*/
ChessBoardType **fillBoard( ChessBoardType **board );

/*
Description: Allocates memory for the chess board.
Input: number of rows and collumns
Output: allocated memory for the chess board
Dependancies: NONE
*/
ChessBoardType **initializeChessBoard( );

/*
Description: highlights the potential attack positions based on the type
Input: chessboard, givenRow, givenCol
Output: highlighted location
Dependancies: NONE
*/
void highlightAttack( ChessBoardType **board, int initialRow, int initialCol,
                       char currentType, char currentTurn, char highlightFlag, int currentState, bool initialPawn );

/*
Description: highlights the potential attack positions for bishop
Input: chessboard, currentRow, currentCol, initial row, initial collomn
Output: highlighted location
Dependancies: NONE
*/
void highlightBishop( ChessBoardType **board, char currentTurn, int initialRow, int initialCol, char highlightFlag );

/*
Description: highlights the potential attack positions for king
Input: chessboard, currentRow, currentCol, initial row, initial collomn
Output: highlighted locations
Dependancies: NONE
*/
void highlightKing( ChessBoardType **board, char currentTurn, int initialRow, int initialCol, char highlightFlag );

/*
Description: highlights the potential attack positions for knight
Input: chessboard, currentRow, currentCol, initial row, initial collomn
Output: highlighted location
Dependancies: NONE
*/
void highlightKnight( ChessBoardType **board, char currentTurn, int initialRow, int initialCol, char highlightFlag );

/*
Description: highlights the potential attack positions for rook
Input: chessboard, currentRow, currentCol, initial row, initial collomn
Output: highlighted location
Dependancies: NONE
*/
void highlightRook( ChessBoardType **board, char currentTurn, int initialRow, int initialCol, char highlightFlag );

/*
Description: highlights the potential attack positions for rook
Input: chessboard, currentRow, currentCol, initial row, initial collomn
Output: highlighted location
Dependancies: NONE
*/
bool isChar( char inputCol );

/*
Description: checks if the player can move a piece to block the current check using copied board method
and checks if the current piece has no obstructions.
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool isCheckmate( ChessBoardType **board, char currentTurn, int currentCode );

/*
Description: Checks every possible move of opponent and checks if the king is in scope
Input: chess board, current turn
Output: NONE
Dependancies: determineType
*/
bool isInCheck(ChessBoardType **board, char turn, char checkCode);

/*
Description: Uses isCheckMate with the flag stalemate to see if any pieces can move
Input: chess board, currentTurn
Output: if the board is in a stalemate
Dependancies: isCheckMate
*/
bool isStalemate( ChessBoardType **board, char currentTurn );

/*
Description: Handles the move piece event based on whos turn it is and what
piece it is.
Input: chess board
Output: NONE
Dependancies: NONE
*/
void movePiece( ChessBoardType **board, char currentTurn,
                               int currentRow, int currentCol, int currentState,
                                                int initialRow, int initialCol);

void outputBoard( ChessBoardType **board );

/*
Description: Starts the game off and handles events
Input: chess board
Output: NONE
Dependancies: NONE
*/
void playGame( ChessBoardType **board );

/*
Description: converts the given row into a usable index
Input: initialRow
Output: NONE
Dependancies: NONE
*/
int rowToIndex( int iniitialRow );

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOpponentKingInCheck(ChessBoardType **board, char currentTurn, int currentRow, int currentCol );

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOutOfCheck( ChessBoardType **board, char currentType, int initialRow, int initialCol, int currentRow, int currentCol, char currentTurn );

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOwnKingInCheck(ChessBoardType **board, char currentTurn, int initialRow, int initialCol, int currentRow, int currentCol);

/*
Description: moves the rook accordingly
Input: chess board, current piece type, current turn,
current row, current column   
Output: Moved pawn piece
Dependancies: checkIfValidPosition
*/
void pieceMoveHelper( ChessBoardType **board, int initialRow, int initialCol, int currentRow, int currentCol, char currentType, char currentTurn );

/*
Description: checks if the current piece can attack
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
void selectNextPosition( ChessBoardType **board, char currentType,
                             char currentTurn, int initialRow, int initialCol, bool *validMove, bool inCheck );

void sendBoard( ChessBoardType **board );

/*
Description: Switches the current turn to the opposite side
Input: current turn
Output: opposite side
Dependancies: NONE
*/
char switchTurn( char currentTurn );


#endif