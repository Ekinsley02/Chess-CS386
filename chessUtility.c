#include "chessUtility.h"

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
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: NONE
*/
ChessBoardType **fillBoard( ChessBoardType **board )
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
Description: Allocates memory for the chess board.
Input: number of rows and collumns
Output: allocated memory for the chess board
Dependancies: malloc w/ sizeof
*/
ChessBoardType **initializeChessBoard( int boardSize )
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