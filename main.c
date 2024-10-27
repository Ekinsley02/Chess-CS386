#include "chessUtility.h"

// Function to output the board and sides to subprocess (Python)
void outputBoard(ChessBoardType **board)
   {
   // initialize functions/variables
      
      int rowIndex, colIndex;

   // Output board (piece types)
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
         
      for (colIndex = 0; colIndex < BOARD_SIZE; colIndex++)
         {
         
         printf("%c ", board[rowIndex][colIndex].type);
         }
         
      printf("\n");
      fflush(stdout);
      }
   }

int main()
   {
   
   // initialize functions/variables
      ChessBoardType **board;
      
   // create game board array
   board = initializeChessBoard( );
   
   // fill the game board with the pieces
   board = fillBoard( board );
   
   // Ensure stdout is unbuffered
   setbuf(stdout, NULL);
   
   // Output initial board
   outputBoard( board );
   
   return(0);
   }