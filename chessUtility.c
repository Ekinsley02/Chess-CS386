#include "chessUtility.h"

#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
#elif defined(__APPLE__)
    #define OS_MAC
#endif

// function definitions

/*
Description: checks if the player can move a piece to block the current check using copied board method
and checks if the current piece has no obstructions.
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool isCheckmate( ChessBoardType **board, char currentTurn, int currentCode )
   {
   // initialize functions/variables
      int rowIndex, colIndex, checkRowIndex = 0, checkColIndex = 0, currentState = MOVING, initialRow, initialCol;
      ChessBoardType **checkedBoard;
      char currentType;
   
   checkedBoard = initializeChessBoard( BOARD_SIZE, BOARD_SIZE );
   
   copyBoard( checkedBoard, board );
   
   
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
      
      for( colIndex = 0; colIndex < BOARD_SIZE; colIndex++ )
         {
         
         initialRow = rowIndex;
         initialCol = colIndex;
         if( board[ rowIndex ][ colIndex ].side == currentTurn )
            {
            
            currentType = board[ rowIndex ][ colIndex ].type;

            // depending on the piece use every possible combination of currentRow and currentCol
            switch( currentType )
               {
                  
               case PAWN:
               if( checkAllValidPawnPositions( board, checkedBoard, currentTurn, currentType, currentState, initialRow, initialCol, currentCode ) ) 
                  {
                           
                  return true;
                  }
                  break;
                  
               case ROOK:
		         if( checkAllValidRookPositions( board, checkedBoard, checkRowIndex, checkColIndex, rowIndex, colIndex, currentType, currentTurn, initialRow, initialCol, currentState, currentCode ) )
                  {
                        
                  return true;
                  }
		            break; 
                  
               case KNIGHT:
               if( checkAllValidKnightPositions( board, checkedBoard, rowIndex, colIndex, currentType, currentTurn, initialRow, initialCol, currentState, currentCode ) )
                  {
                        
                  return true;
                  }
                  break;
                  
               
               case BISHOP:
               if( checkIfAllValidBishopPositions( board, checkedBoard, checkRowIndex, checkColIndex, rowIndex, colIndex, currentType, currentTurn, initialRow, initialCol, currentState, currentCode ) )
                  {
                           
                  return true;
                  }
                  break;

               case QUEEN:
               if( checkAllValidRookPositions( board, checkedBoard, checkRowIndex, checkColIndex, rowIndex, colIndex, currentType, currentTurn, initialRow, initialCol, currentState, currentCode ) || checkIfAllValidBishopPositions( board, checkedBoard, checkRowIndex, checkColIndex, rowIndex, colIndex, currentType, currentTurn, initialRow, initialCol, currentState, currentCode ) )
                  {
                        
                  return true;
                  }
                  break;
                  
               case KING:
               if( checkAllValidKingPositions( board, checkedBoard, currentTurn, currentType, currentState, initialRow, initialCol ) )
                  {
                  
                  return true;
                  }
                  break;
                  
               }
            }
         }
      }
     
   // clear temporary check board for data leaks
   for( int i = 0; i < BOARD_SIZE; i++ ) 
      {
         
      free( checkedBoard[ i ] );
      }
      
   free( checkedBoard );

   return false;
   }


/*
Description: checks if the given position is in view for battle
and checks if the current piece has no obstructions.
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkIfValidPosition( ChessBoardType **board, char currentType,
                           char currentTurn, int initialRow, int initialCol, int currentRow, int currentCol, int *currentState, bool initialPawn )
   {

   // sort the current type
   switch( currentType )
      {
     
     case PAWN:
         if( checkPawnPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState, initialPawn ) )
            {
            
            return true;
            }
         break;

      case ROOK:
         if( checkRookPositions(board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) || *currentState == SELECTING )
            {
         
             return true;
            }
         break;

      case KNIGHT:
         // Add logic for knight
         if( checkKnightPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) || *currentState == SELECTING )
            {
         
            return true;
            }
         break;
      

      case BISHOP:
         // Add logic for bishop
         if( checkBishopPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) || *currentState == SELECTING )
            {
         
            return true;
            }
         break;

      case QUEEN:
         if( checkBishopPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) || checkRookPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) || *currentState == SELECTING  )
            {
         
            return true;
            }
         break;

      case KING:
         if( checkKingPositions( board, currentTurn, currentRow, currentCol, initialRow, initialCol, currentState ) ) 
            {
            
            return true;
            }
         break;
      }
   
   return false;
   }


/*
Description: converts the players column input to an index
Input: players chosen column
Output: the index from the given column
Dependancies: NONE
*/
int columnToIndex( char chosenCol )
   {

   // determine the chosen collum
      // return appropriate index
   switch( chosenCol )
      {

      case 'H':
      case 'h':
         return 0;
         break;
         
      case 'G':
      case 'g':
         return 1;
         break;
         
      case 'F':
      case 'f':
         return 2;
         break;
         
      case 'E':
      case 'e':
         return 3;
         break;
         
      case 'D':
      case 'd':
         return 4;
         break;
         
      case 'C':
      case 'c':
         return 5;
         break;
         
      case 'B':
      case 'b':
         return 6;
         break;
         
      case 'A':
      case 'a':
         return 7;
         break;
         
      default:
         return -1;
         break;
      }

   }


/*
Description: Copies the current board to another board, used for looking into the next move
Input: destination board, source board
Output: copied board from source
Dependancies: NONE
*/
void copyBoard( ChessBoardType **destinationBoard, ChessBoardType **sourceBoard )
   {
   // initialize functions/variables
      int rowIndex, colIndex;
      
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
      
      for( colIndex = 0; colIndex < BOARD_SIZE; colIndex++ )
         {
         
         destinationBoard[ rowIndex ][ colIndex ].type = sourceBoard[ rowIndex ][ colIndex ].type;
         destinationBoard[ rowIndex ][ colIndex ].side = sourceBoard[ rowIndex ][ colIndex ].side;
         destinationBoard[ rowIndex ][ colIndex ].highlight = sourceBoard[ rowIndex ][ colIndex ].highlight;
         }
         
      }
   
   }


/*
Description: determines the opposite side guven the current side
Input: currentTurn
Output: The opposite of the current side
Dependancies: NONE
*/
char determineOppositeSide( char currentTurn )
   {
   if( currentTurn == 'P' )
      {
      
      return 'O';
      }
   
   else if( currentTurn == 'O' )
      {
      
      return 'P';
      }
   
   // if not given a valid current turn return X
   return 'X';
   }

/*
Description: determines the sides of the pieces on initial board
Input: Chessboard
Output: The pieces on the board sides identified
Dependancies: NONE
*/
void determineSides( ChessBoardType **board )
   {

   // initialize functions/variables
      int boardRowIndex, boardColIndex;
   
   // set the first 16 chess pieces members to oponent
   for( boardRowIndex = 0; boardRowIndex < 2; boardRowIndex++ )
      {

      for( boardColIndex = 0; boardColIndex < 8; boardColIndex++ )
         {

         board[ boardRowIndex ][ boardColIndex ].side = 'O';
         }
      }

   // set the last 16 chess pieces to player
   for( boardRowIndex = 6; boardRowIndex < 8; boardRowIndex++ )
      {

      for( boardColIndex = 0; boardColIndex < 8; boardColIndex++ )
         {

         board[ boardRowIndex ][ boardColIndex ].side = 'P';
         }

      }

   }
   
/*
Description: finds the piece type of the given board row and column
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
char determineType( ChessBoardType **board, int boardRow, int boardCol )
   {

   // return the type at given position
   return board[ boardRow][ boardCol ].type;
   }

/*
Description: prints the bottom half of the board, after the pieces.
 Also determines which opperating system is used.
Input: NONE
Output: printed lower chess board
Dependancies: NONE
*/
void displayBottomBoard()
   {

   #ifdef OS_WINDOWS
   
      printf("|  |                          |  |\n");
      printf("|  +--------------------------+  |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|                                |\n");
      printf("|                                |\n");
      printf("+--------------------------------+\n");
   #elif defined(OS_MAC)
      
      printf("|  |                          |  |\n");
      printf("|  └--------------------------┘  |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|                                |\n");
      printf("|                                |\n");
      printf("└--------------------------------┘\n");
      
   #else
      
      printf("|  |                          |  |\n");
      printf("|  +--------------------------+  |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|                                |\n");
      printf("|                                |\n");
      printf("+--------------------------------+\n");
      
   #endif
   }

/*
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: printTopBoard,
*/
void displayChessBoard( ChessBoardType **board, int rows, int cols )
   {

   // initilaize functions/variables
      int rowIndex, colIndex, rowNum = BOARD_SIZE;
      char bar = '|';
   
   // print a buffer from the other text
   printf("\n\n\n\n\n\n\n\n\n\n");
   
   // display the top segment of the board
   displayTopBoard();
   
   for( rowIndex = 0; rowIndex < rows; rowIndex++ )
      {
         
      printf( "%c %d%c", bar, rowNum, bar );
      
      for( colIndex = 0; colIndex < cols; colIndex++ )
         { 

         if( board[ rowIndex ][ colIndex ].highlight == true )
            {

            printf( GREEN_TEXT "%3c" RESET_TEXT,
                                          board[ rowIndex ][ colIndex ].type );
            }
         
        else if( board[ rowIndex ][ colIndex ].castlePos == true )
        	{
        	printf( YELLOW_TEXT "%3c" RESET_TEXT,
                                          board[ rowIndex ][ colIndex ].type );
        	}
         
            
         else if( board[ rowIndex ][ colIndex ].side == 'O' )
            {

            printf( RED_TEXT "%3c" RESET_TEXT,
                                          board[ rowIndex ][ colIndex ].type );
            }
            
         else if( board[ rowIndex ][ colIndex ].side == 'P' )
            {

            printf( BLUE_TEXT "%3c" RESET_TEXT,
                                          board[ rowIndex ][ colIndex ].type );
            }
            
         else
            {

            printf( "%3c", board[ rowIndex ][ colIndex ].type );
            }

         }
         
      printf("%3c%d %c", bar, rowNum, bar);
      
      rowNum = rowNum - 1;
      
      printf("\n");
      }
      
   displayBottomBoard();
   }

/*
Description: prints the upper half of the board, before the pieces.
 Also determines which opperating system is used.
Input: NONE
Output: printed upper chess board
Dependancies: NONE
*/
void displayTopBoard()
   {
   #ifdef OS_WINDOWS
      
      printf("+--------------------------------+\n");
      printf("|                                |\n");
      printf("|                                |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|  +--------------------------+  |\n");
      printf("|  |                          |  |\n");
      
   #elif defined(OS_MAC)
      
      printf("┌--------------------------------┐\n");
      printf("|                                |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|  ┌--------------------------┐  |\n");
      printf("|  |                          |  |\n");
      
   #else
      
      printf("+--------------------------------+\n");
      printf("|                                |\n");
      printf("|                                |\n");
      printf("|     H  G  F  E  D  C  B  A     |\n");
      printf("|  +--------------------------+  |\n");
      printf("|  |                          |  |\n");
   #endif
   }



/*
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: NONE
*/
ChessBoardType **fillBoard( ChessBoardType **board)
   {
   
      // initilaize functions/variables
      int rowIndex, colIndex;

      // create the initial boards layout
      char initialPieces[] =
      {
       'R', 'G', 'B', 'Q', 'K', 'B', 'G', 'R',
       'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
       'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',
       'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',
       'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',
       'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X',
       'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
       'R', 'G', 'B', 'Q', 'K', 'B', 'G', 'R',
      };

   // fill the board with the appropriate types and NON player
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {

      for( colIndex = 0; colIndex < BOARD_SIZE; colIndex++ )
         {

         board[ rowIndex ][ colIndex ].type = initialPieces[ rowIndex * BOARD_SIZE + colIndex ];
         board[ rowIndex ][ colIndex ].side = NON_PLAYER;
         board[ rowIndex ][ colIndex ].highlight = false;
         board[ rowIndex ][ colIndex ].hasMoved = false;
         board[ rowIndex ][ colIndex ].castlePos = false;
         }

      }

   // determines the sides of every piece
   determineSides( board );
   return board;
   }

/*
Description: highlights the potential attack positions based on the type
Input: chessboard, givenRow, givenCol
Output: highlighted location
Dependancies: NONE
*/
void highlightAttack( ChessBoardType **board, int initialRow, int initialCol,
                       char currentType, char currentTurn, char highlightFlag, int currentState, bool initialPawn )
   {
  
   // check current battle state
   if( currentState == PASSIVE || currentState == BOTH || currentState == SELECTING )
      {

      // checks if the flag is highlight
      if( highlightFlag == HIGHLIGHT )
         {
            
            switch( currentType )
               {
                  
               case PAWN:
                  if( currentTurn == 'P' )
                     {
                        
                     if( initialRow > 0 && !( putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, initialRow - 1, initialCol ) ) )
                        {
                           
                        board[ initialRow - 1 ][ initialCol ].highlight = true;
                        }
                     // if it is the first move of pawn, highlight the next two
                     if( initialPawn && !( putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, initialRow - 2, initialCol ) ) )
                        {
                        
                        board[ initialRow - 2 ][ initialCol ].highlight = true;
                        }
                     }
                  else if( currentTurn == 'O' )
                     {
                        
                     if( initialRow < BOARD_SIZE - 1 && !( putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, initialRow + 1, initialCol ) ) )
                        {
                           
                        board[ initialRow + 1 ][ initialCol ].highlight = true;
                        }
                     // if it is the first move of pawn, highlight the next two
                     if( initialPawn && !( putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, initialRow + 2, initialCol ) ) )
                        {
                           
                        board[ initialRow + 2 ][ initialCol ].highlight = true;
                        }
                     }
                  break;

            case ROOK:

               highlightRook( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case KNIGHT:

               highlightKnight( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case BISHOP:

               highlightBishop( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case QUEEN:

               highlightBishop( board, currentTurn, initialRow, initialCol, highlightFlag );
               highlightRook( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case KING:
               highlightKing( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;
            }
         }

      // checks if the flag is dehighlight
      else if( highlightFlag == DEHIGHLIGHT ) 
         {
         switch( currentType )
            {

            case PAWN:
               if(  currentTurn == 'P' )
                  {
                  
                  if( initialRow > 0 )
                     {
                  
                     board[ initialRow - 1 ][ initialCol ].highlight = false;
                     }
                  if( initialPawn )
                     {
                  
                     board[ initialRow - 2 ][ initialCol ].highlight = false;
                     }
                  }
               else if( currentTurn == 'O' )
                  {
                  
                  if (initialRow < BOARD_SIZE - 1)
                     {
                  
                     board[ initialRow + 1 ][ initialCol ].highlight = false;
                     }
                  if( initialPawn )
                     {
                  
                     board[ initialRow + 2 ][ initialCol ].highlight = false;
                     }
                  }
               break;

            case ROOK:
               highlightRook( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case KNIGHT:
               highlightKnight( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case BISHOP:
               highlightBishop( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case QUEEN:
               highlightRook( board, currentTurn, initialRow, initialCol, highlightFlag );
               highlightBishop( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;

            case KING:
               highlightKing( board, currentTurn, initialRow, initialCol, highlightFlag );
               break;
            }
         }
      }


   if( currentState == BATTLE || currentState == BOTH )
      {
         
      // checks if the flag is highlight
      if( highlightFlag == HIGHLIGHT )
         {
            
         switch( currentType )
            {
               
            case PAWN:
               if( currentTurn == 'P' && initialRow > 0 && initialCol >= 0 )
                  {
                  
                  // check left edge pieces for battle highlighting
                  if( !( checkEdgePieceLeft( board, initialCol ) ) && board[ initialRow - 1 ][ initialCol + 1 ].side == 'O' )
                     {
                     
                     board[ initialRow - 1 ][ initialCol + 1 ].highlight = true;
                     }
                     
                  // check left edge pieces for battle highlighting
                  if( !( checkEdgePieceRight( board, initialCol ) ) && board[ initialRow - 1 ][ initialCol - 1 ].side == 'O' )
                     {
                  
                     board[ initialRow - 1 ][ initialCol - 1 ].highlight = true;
                     }
                  }
               else if( currentTurn == 'O' && initialRow < BOARD_SIZE - 1 && initialCol >= 0 )
                  {
                     
                  // check left edge pieces for battle highlighting
                  if( !(checkEdgePieceLeft( board, initialCol ) ) && board[ initialRow + 1 ][ initialCol + 1 ].side == 'P' )
                     {
                  
                     board[ initialRow + 1 ][ initialCol + 1 ].highlight = true;
                     }
                     
                  // check right edge pieces for battle highlighting
                  if( !( checkEdgePieceRight( board, initialCol ) ) && board[ initialRow + 1 ][ initialCol - 1 ].side == 'P' )
                     {
                  
                     board[ initialRow + 1 ][ initialCol - 1 ].highlight = true;
                     }
                  }
               break;

            }
         }

         // checks if the flag is dehighlight
      else if( highlightFlag == DEHIGHLIGHT ) 
         {
         switch( currentType )
            {

            case PAWN:
               if( currentTurn == 'P' && initialRow > 0 && initialCol >= 0 )
                  {
                  // check left edge pieces for battle highlighting
                  if( !( checkEdgePieceLeft( board, initialCol ) ) && board[ initialRow - 1 ][ initialCol + 1 ].highlight )
                     {
                        
                     board[ initialRow - 1 ][ initialCol + 1 ].highlight = false;
                     }
                     
                  // check left edge pieces for battle highlighting
                  if( !( checkEdgePieceRight( board, initialCol ) ) && board[ initialRow - 1 ][ initialCol - 1 ].highlight )
                     {

                     board[ initialRow - 1 ][ initialCol - 1 ].highlight = false;
                     }
                  }
               // check left edge pieces for battle highlighting
               else if( currentTurn == 'O' && initialRow < BOARD_SIZE - 1 && initialCol >= 0 )
                  {
                  
                  if( !( checkEdgePieceLeft( board, initialCol ) ) && board[ initialRow + 1 ][ initialCol + 1 ].highlight )
                     {
                  
                     board[ initialRow + 1 ][ initialCol + 1 ].highlight = false;
                     }
                     
                  // check right edge pieces for battle highlighting
                  if( !( checkEdgePieceRight( board, initialCol ) ) && board[ initialRow + 1 ][ initialCol - 1 ].highlight )
                     {
                  
                     board[ initialRow + 1 ][ initialCol - 1 ].highlight = false;
                     }
                  }
               break;
            }
         }
      }
   }

