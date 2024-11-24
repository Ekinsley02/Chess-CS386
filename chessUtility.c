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

/*
Description: Allocates memory for the chess board.
Input: number of rows and collumns
Output: allocated memory for the chess board
Dependancies: malloc w/ sizeof
*/
ChessBoardType **initializeChessBoard( )
   {
   // iniitlaize functions/variables
       ChessBoardType **newBoard;
       int index;

   newBoard = ( ChessBoardType ** )malloc( BOARD_SIZE * sizeof( ChessBoardType * ) );

   for( index = 0; index < BOARD_SIZE; index++ )
      {

      newBoard[ index ] = ( ChessBoardType * )malloc
                                           ( BOARD_SIZE * sizeof( ChessBoardType ) );
      }

   return newBoard;
   }

bool isChar( char inputCol )
    {
        
    return isalpha( inputCol );
    }

/*
Description: Checks every possible move of opponent and checks if the king is in scope
Input: chess board, current turn
Output: NONE
Dependancies: determineType
*/
bool isInCheck(ChessBoardType **board, char turn, char checkCode)
   {
    int rowIndex, colIndex;
    char currentType, currentTurn;
    int currentState = CHECK;

    // Iterate over the entire board
    for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
         
        for( colIndex = 0; colIndex < BOARD_SIZE; colIndex++ ) 
           {
              
            currentType = board[ rowIndex ][ colIndex ].type;
            currentTurn = board[ rowIndex ][ colIndex ].side;

            // Only check positions of the specified turn
            if( currentTurn == turn && checkCode == PUTCHECK )
               {
                  
                // Check if the current piece can move to a position that puts the opponent in check
                if( checkIfValidPosition( board, currentType, currentTurn, rowIndex, colIndex, rowIndex, colIndex, &currentState, false ) )
                  {
                     
                    if( currentState == CHECK )
                       {
                          
                        return true;
                       }
                    }
               }
               
            if( checkCode == INCHECK )
               {
                  
               if( checkIfValidPosition( board, currentType, currentTurn, rowIndex, colIndex, rowIndex, colIndex, &currentState, false ) )
                  {
                     
                   if( currentState == CHECK )
                     {
                    
                     return true;
                     }
                  }
               }
           }
      }

    // If no piece can put the opponent in check, return false
    return false;
   }

/*
Description: Uses isCheckMate with the flag stalemate to see if any pieces can move
Input: chess board, currentTurn
Output: if the board is in a stalemate
Dependancies: isCheckMate
*/
bool isStalemate( ChessBoardType **board, char currentTurn )
    {
    
    if( !isCheckmate( board, currentTurn, STALEMATE ) )
        {
        
        return true;
        }
    
    return false;
    }

/*
Description: Handles the move piece event based on whos turn it is and what
piece it is.
Input: chess board
Output: NONE
Dependancies: determineType, pieceHelperPawn
*/
void movePiece( ChessBoardType **board, char currentTurn,
                               int currentRow, int currentCol, int currentState,
                                                int initialRow, int initialCol )
   {
   // initialize functions/variables
      char currentType;

   // determine the type of chess piece played
   currentType = determineType( board, initialRow, initialCol );

   // determine if it is the players turn
      // handle the event of each piece
   switch( currentType )
      {

      case PAWN:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
       
      case ROOK:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
      
      case KNIGHT:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
      
      case BISHOP:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
      
      case KING:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
      
      case QUEEN:
         pieceMoveHelper( board, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );
         break;
      }
   
   // mark that the piece has been moved at least once
   board[ currentRow ][ currentCol ].hasMoved = true;
   }

/*
Description: Starts the game off and handles events
Input: chess board
Output: NONE
Dependancies: displayChessBoard, columnToIndex, determineType,
 checkForBattle, battleHandler, movePiece
*/
void playGame( ChessBoardType **board )
   {
   // initialize functions/variables
      bool gameFlag = true, validMove, inCheck = false;
      int initialRow, colIndex, rowIndex;
      char initialCol, type = NON_PLAYER, winner[ 6 ];
      // control whos turn it is
      char currentTurn = 'P';
      int result;
   
      
   displayChessBoard( board, BOARD_SIZE, BOARD_SIZE );
   
   while( gameFlag == true )
      {

      validMove = false;
      if( currentTurn == 'P' )
         {

         printf( "\nCurrent turn: BLUE" );
         }

      else
         {

         printf( "\nCurrent turn: RED" );
         }
      
      if( isInCheck( board, currentTurn, INCHECK ) )
         {  
        
         if( !isCheckmate( board, currentTurn, NONE ) )
            {
               
            if( currentTurn == 'P' )
               {
                  
               strcpy(winner, "RED");
               }
               
            if( currentTurn == 'O' )
               {
                  
               strcpy(winner, "BLUE");
               }
            
            printf( "\nYour checkmated! %s wins!", winner );
            
            gameFlag = false;
            
            break;
            }
            
         printf( "\nYour in check!" );
         
         inCheck = true;  
         }
         
      else if( isStalemate( board, currentTurn ) )
        {
        
        printf( "\nKing stalemated! Its a tie!" );
        
        gameFlag = false;
        } 
      
      
    do 
        {
        printf("\nEnter row: ");
        result = scanf("%d", &initialRow);

        // Check if the input is valid
        if( result != 1 ) 
        
            {
            printf("Invalid input. Please enter an integer.\n");

            // Clear the invalid input
            while (getchar() != '\n');
            }
        
        } while (result != 1);
        
      rowIndex = rowToIndex( initialRow );
      
      printf( "\nenter col:" );  

      scanf( " %c", &initialCol );
        
      // exit game if q is typed
      if( initialCol == 'Q' || initialCol == 'q' )
         {
            
         gameFlag = false;
         break;
         }
      
      colIndex = columnToIndex( initialCol );
      printf("\n col: %d", colIndex );
      type = determineType( board, rowIndex, colIndex );
      
      // make sure the user inputs their piece and its in bounds
      if( board[ rowIndex ][ colIndex ].side == currentTurn && rowIndex >= 0 && colIndex >= 0 && rowIndex < BOARD_SIZE && colIndex < BOARD_SIZE ) 
         {
            
         selectNextPosition( board, type, currentTurn, rowIndex, colIndex, &validMove, inCheck );
         displayChessBoard( board, BOARD_SIZE, BOARD_SIZE );
         }
      else
         {
            
         displayChessBoard( board, BOARD_SIZE, BOARD_SIZE );
         printf( "\nInvalid choice please try again" );
         validMove = false;
         }

      if( validMove == true )
         {

         currentTurn = switchTurn( currentTurn );  
         }    
      }
   }

/*
Description: converts the given row into a usable index
Input: initialRow
Output: NONE
Dependancies: NONE
*/
int rowToIndex( int initialRow )
    {
    // initialize functions/variables
        // create a array of rows
        int rowIndexes[ BOARD_SIZE ] = { 7, 6, 5, 4, 3, 2, 1, 0 };
    
    return rowIndexes[ initialRow - 1 ];
    }

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOpponentKingInCheck(ChessBoardType **board, char currentTurn, int currentRow, int currentCol)
   {
   // initialize functions/variables
      char oppositeTurn;
      
   oppositeTurn = determineOppositeSide( currentTurn );
   
   return isInCheck( board, oppositeTurn, INCHECK );
   }

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOutOfCheck( ChessBoardType **board, char currentType, int initialRow, int initialCol, int currentRow, int currentCol, char currentTurn, bool initialPawn )
   {
   // intiialize functions/variables
      ChessBoardType **checkedBoard;
   
   int currentState = MOVING;

   checkedBoard = initializeChessBoard( BOARD_SIZE, BOARD_SIZE );
   
   copyBoard( checkedBoard, board );
   
   pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

   if( !isInCheck( checkedBoard, currentTurn, INCHECK ) && currentRow != initialRow && currentCol != initialCol && checkIfValidPosition( checkedBoard, currentType,
                           currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, initialPawn ))
      {
      
      return true;
      }
   
   return false;
   }

/*
Description: creates a new board with the players given move and analyses if it would put the king into check
Input: board, initialRow, initialCol, chosenRow, chosenCol
Output: if the players move will put the king into check
Dependancies: isInCheck
*/
bool putsOwnKingInCheck( ChessBoardType **board, char currentTurn, int initialRow, int initialCol, int currentRow, int currentCol )
   {
   // initialize functions/variables
      ChessBoardType **checkedBoard;
      int rowIndex;
      char currentType, oppositeTurn;
      bool result;
   
   checkedBoard = initializeChessBoard( BOARD_SIZE, BOARD_SIZE );
   
   copyBoard( checkedBoard, board );
   
   currentType = determineType( board, initialRow, initialCol );
   
   pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

   oppositeTurn = determineOppositeSide( currentTurn );
   
   result = isInCheck( checkedBoard, oppositeTurn, PUTCHECK );
   
   // Free memory to avoid leaks
   for( rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++ )
      {
         
      free(checkedBoard[ rowIndex ]);
      }
      
   free( checkedBoard );
   
   return result;
   }
/*
Description: checks if the current piece can attack
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: highlightAttack, displayChessBoard, columnToIndex,
 checkForBattle, movePiece
*/
void selectNextPosition(ChessBoardType **board, char currentType,
                             char currentTurn, int initialRow, int initialCol, bool *validMove, bool inCheck)
   {
   // initialize functions/variables
      int currentRow, colIndex, currentState = SELECTING;
      char currentCol;
      bool initialPawn;

   // check if the piece is the first pawn used
   if( currentTurn == 'P' && board[ initialRow ][ initialCol ].type == PAWN && initialRow == 6 )
      {
         
      initialPawn = true;
      }
   else if( currentTurn == 'O' && board[ initialRow ][ initialCol ].type == PAWN && initialRow == 1 )
      {
         
      initialPawn = true;
      }
   else
      {
         
      initialPawn = false;
      }

   // not very optimum, uses currentRow/Col twice, hard to rework since checkIfValidPosition is used twice for every piece
   if( checkIfValidPosition( board, currentType, currentTurn, initialRow, initialCol, initialRow, initialCol, &currentState, initialPawn ) )
      {
         
      // highlight potential attack points using HIGHLIGHT flag
      highlightAttack( board, initialRow, initialCol, currentType, currentTurn, HIGHLIGHT, currentState, initialPawn );

      displayChessBoard( board, BOARD_SIZE, BOARD_SIZE );

      highlightAttack( board, initialRow, initialCol, currentType, currentTurn, DEHIGHLIGHT, currentState, initialPawn );
      }

   // change the state to moving a piece instead of selecting for highlighting
   currentState = MOVING;

   // prompt where the user would like to attack
   printf( "\nWhere would you like to move this piece?" );
   printf("\nenter row:");

   scanf( "%d", &currentRow );
   
   currentRow = rowToIndex( currentRow );
   
   printf( "\nenter column:" );
   
   scanf( " %c", &currentCol );

   // convert the column to index
   colIndex = columnToIndex( currentCol );
   

   // check if valid position using moving piece conditions
   if( ( inCheck && putsOutOfCheck( board, currentType, initialRow, initialCol, currentRow, currentCol, currentTurn, initialPawn ) ) || ( checkIfValidPosition( board, currentType, currentTurn, initialRow, initialCol, currentRow, colIndex, &currentState, initialPawn ) ) )
      {
         
      if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, colIndex ) )
         {
            
         movePiece( board, currentTurn, currentRow, colIndex, currentState, initialRow, initialCol );
         *validMove = true;
         
         if( putsOpponentKingInCheck( board, currentTurn, currentRow, colIndex ) )
            {
               
            printf( "\nCheck!" );
            }
         }
      else
         {
            
         printf( "\nCannot put your own king in check, try again" );
         *validMove = false;
         }
      }
   else
      {
         
      printf( "\nInvalid move, please try again" );
      *validMove = false;
      }
   }


/*
Description: Switches the current turn to the opposite side
Input: current turn
Output: opposite side
Dependancies: NONE
*/
char switchTurn( char currentTurn )
   {

   if( currentTurn == 'P' )
      {

      return 'O';
      }
   else
      {

      return 'P';
      }
   }
