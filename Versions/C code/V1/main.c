// include libraries and constants
#include "chessUtility.h"


int main()
	{

    // initialize functions/variables
        ChessBoardType **chessBoard;

        bool keepPlaying = true;

        char inputChar;


    // create game board array
    chessBoard = initializeChessBoard( BOARD_SIZE, BOARD_SIZE );

   // fill the game board with the pieces
    chessBoard = fillBoard( chessBoard, BOARD_SIZE, BOARD_SIZE );
    
    
    do
       {
        printf( "\nWeclome to my game of chess\n" );
        printf( "\n----------------------------" );
        printf( "\nMAIN MENU" );
        printf( "\n1. (n)ew game." );
        printf( "\n2. (e)xit game." );
        printf("\nYour choice: ");
        scanf( " %c", &inputChar );

        switch( inputChar)
            {
            // case one: player chooses to play chess.
            case '1':
            case 'N':
            case 'n':
               playGame( chessBoard );
               keepPlaying = false;
               break;
            
            // case two: player chooses to quit.
            case '2':
            case 'E':
            case 'e':
               printf( "\nExit.\n" );
               keepPlaying = false;
               break;
               
            // default case: player doesn't give calid entry.
            default:
               printf( "\nInvalid option, please try again." );
            }

       }while( keepPlaying );



   printf( "\nExiting program..\n" );
	return 0;
	}