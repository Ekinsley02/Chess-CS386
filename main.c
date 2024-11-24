#include "chessUtility.h"

// Function to output the board and sides to subprocess (Python)
void outputBoard(ChessBoardType **board, int gameCondition)
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
   printf("%d\n", gameCondition);
   }

int main()
   {
   
   // initialize functions/variables
      ChessBoardType **board;
      
      char currentType, currentTurn;
      
      bool initialPawn = false, gameRunning = true;
      
      int start_row = 0, start_col = 0, end_row = 0, end_col = 0;
      
      int currentState = SELECTING, gameCondition = 0;
      
      bool inCheck = false;
      
   // create game board array
   board = initializeChessBoard( );
   
   // fill the game board with the pieces
   board = fillBoard( board );
   
   // Ensure stdout is unbuffered
   setbuf(stdout, NULL);
   
   // Output initial board
   outputBoard( board, gameCondition );
   
   currentTurn = 'P';
   
   while (gameRunning)
      {
      
      initialPawn = false;
      inCheck = false;
      
      if( gameCondition == 1 || gameCondition == 2 )
         {
         
         gameRunning = false;
         outputBoard( board, gameCondition );
         }

      scanf( "%d %d", &start_row, &start_col );
         
      currentType = board[start_row][start_col].type;

      // Check if the piece is the first pawn moved
      if( start_row == 6 && currentTurn == 'P' && currentType == PAWN )
         {
            
         initialPawn = true;
         }
        
      else if ( start_row == 1 && currentTurn == 'O' && currentType == PAWN )
        {
           
         initialPawn = true;
        }
      
      
      // Process the move if valid for highlighting
      if( checkIfValidPosition( board, currentType, currentTurn, start_row, start_col, start_row, start_col, &currentState, initialPawn ) )
         {

         highlightAttack( board, start_row, start_col, currentType, currentTurn, HIGHLIGHT, currentState, initialPawn );
            
         fflush(stdout);
         }
         
      outputBoard( board, gameCondition );

      scanf( "%d %d", &end_row, &end_col );

      highlightAttack( board, start_row, start_col, currentType, currentTurn, DEHIGHLIGHT, currentState, initialPawn );
   
      currentState = MOVING;

      if( isInCheck( board, currentTurn, INCHECK ) )
         {
         
         inCheck = true;
         }
        
      // Process the move if valid for moving
      if( (inCheck && putsOutOfCheck( board, currentType, start_row, start_col, end_row, end_col, currentTurn, initialPawn ) ) || ( checkIfValidPosition( board, currentType, currentTurn, start_row, start_col, end_row, end_col, &currentState, initialPawn ) ) )
         {
            
         if( !putsOwnKingInCheck( board, currentTurn, start_row, start_col, end_row, end_col ) )
            {
               
            movePiece(board, currentTurn, end_row, end_col, currentState, start_row, start_col);
            
            currentTurn = switchTurn( currentTurn );  

            if( isInCheck( board, currentTurn, INCHECK ) )
               {
               
               inCheck = true;
               }

            if( inCheck && !isCheckmate( board, currentTurn, NONE ) )
               {  
         
               gameCondition = 1;
               }
            
            else if( !inCheck && isStalemate( board, currentTurn ) )
               {
        
               gameCondition = 2;
               }
            }
         }
      
      outputBoard( board, gameCondition );
      
      currentState = SELECTING;
      }
	}