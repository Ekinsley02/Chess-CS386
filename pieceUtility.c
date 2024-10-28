#include "chessUtility.h"

/*
Description: checks all valid positions for the rook
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkIfAllValidBishopPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int checkRowIndex, int checkColIndex, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode )
   {
      
   // initialize functions/variables
      // initialize current row/col indexes
      int currentRow, currentCol;
   for( checkRowIndex = rowIndex - 1, checkColIndex = colIndex - 1; checkRowIndex >= 0 && checkColIndex >= 0; checkRowIndex--, checkColIndex--)
      {
      
      currentRow = checkRowIndex;
      currentCol = checkColIndex;
      if( checkIfValidPosition( checkedBoard, currentType, currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, false ) )
            {
               
            if( currentCode == STALEMATE )
               {
                      
               if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, currentCol ) )
                  {
                  
                  return true;
                  }
               }
               
            pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

            if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
               {
               
               return true;
               }
               
            else
               {
            
               copyBoard( checkedBoard, board );
               }
            }
      }
   
      for( checkRowIndex = rowIndex - 1, checkColIndex = colIndex + 1; checkRowIndex >= 0 && checkColIndex < BOARD_SIZE; checkRowIndex--, checkColIndex++ )
         {

         currentRow = checkRowIndex;
         currentCol = checkColIndex;
      
         if( checkIfValidPosition( checkedBoard, currentType, currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, false ) )
            {
            
              if( currentCode == STALEMATE )
                  {
                      
                  if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, currentCol ) )
                     {
                  
                     return true;
                     }
                  }
            
            pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

            if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
               {
         
               return true;
               }
               
            else
               {
         
               copyBoard( checkedBoard, board );
               }
            }
         }

   for( checkRowIndex = rowIndex + 1, checkColIndex = colIndex + 1; checkRowIndex < BOARD_SIZE && checkColIndex < BOARD_SIZE; checkRowIndex++, checkColIndex++  )
      {

      currentRow = checkRowIndex;
      currentCol = checkColIndex;
   
      if( checkIfValidPosition( checkedBoard, currentType, currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, false ) )
         {
              
              if( currentCode == STALEMATE )
                  {
                      
               if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, currentCol ) )
                  {
                  
                  return true;
                  }
                  }
              
         pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

         if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
               {
           
               return true;
               }
         else
               {
           
               copyBoard( checkedBoard, board );
               }
               }
         }

      for( checkRowIndex = rowIndex + 1, checkColIndex = colIndex - 1; checkRowIndex < BOARD_SIZE && checkColIndex >= 0; checkRowIndex++, checkColIndex-- )
          {

          currentRow = checkRowIndex;
          currentCol = checkColIndex;
           
          if( checkIfValidPosition( checkedBoard, currentType, currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, false ) )
              {
                   
                  if( currentCode == STALEMATE )
                      {
                  if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, currentCol ) )
                     {
                     
                     return true;
                     }
                      }
                    
              pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

              if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
                 {
                 
                 return true;
                 }

              else
                 {
                 
                 copyBoard( checkedBoard, board );
                 }
              }
          }
                 
   return false;
   }
