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
   
   // Output sides (Player or Opponent)
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
      for (colIndex = 0; colIndex < BOARD_SIZE; colIndex++)
         {
            
         printf("%c ", board[rowIndex][colIndex].side);
         }
         
      printf("\n");
      fflush(stdout);
      }
      
   // Output highlights (1 or 0 dependining on highlight)
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
         
      for( colIndex = 0; colIndex < BOARD_SIZE; colIndex++ )
         {
            
         printf("%d ", board[rowIndex][colIndex].highlight);
         }
         
      printf("\n");
      fflush(stdout);
      }
   }

int main()
   {
   
   // initialize functions/variables
      ChessBoardType **board;
      
      char currentType, currentTurn;
      
      bool initialPawn = false, gameRunning = true;
      
      int start_row = 0, start_col = 0;
      
      int currentState = SELECTING;
      
   // create game board array
   board = initializeChessBoard( );
   
   // fill the game board with the pieces
   board = fillBoard( board );
   
   // Ensure stdout is unbuffered
   setbuf(stdout, NULL);
   
   // Output initial board
   outputBoard( board );
   
   currentTurn = 'P';
   
   while( gameRunning )
      {
      
      if( scanf( "%d %d", &start_row, &start_col ) != 2 ) 
         {
            
         printf("Invalid input, exiting loop.\n");
         fflush(stdout);
         break;
         }
         
      currentType = board[start_row][start_col].type;
      
      // Process the move if valid for highlighting
      if( checkIfValidPosition( board, currentType, currentTurn, start_row, start_col, start_row, start_col, &currentState, initialPawn ) )
         {
               
         // highlight potential attack points using HIGHLIGHT flag
         printf("Highlighting potential moves.\n");
         fflush(stdout);
         highlightAttack( board, start_row, start_col, currentType, currentTurn, HIGHLIGHT, currentState, initialPawn );
            
         printf("Outputting board with highlights.\n");
         fflush(stdout);
         }
         
      outputBoard(board);
      }
   
   return(0);
   }