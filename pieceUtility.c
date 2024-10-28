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

/*
Description: checks all valid positions for the King
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidKingPositions( ChessBoardType **board, ChessBoardType **checkedBoard, char currentTurn,
                                                char currentType, int currentState, int initialRow, int initialCol )
   {
   
   // check if top left is available
   if( initialRow > 0 && initialCol > 0 && board[ initialRow - 1 ][ initialCol - 1 ].side != currentTurn )
      {

      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow - 1, initialCol - 1, currentType, currentTurn );
      
      // check if prjection puts out of check
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      // otherwise still in check, copy board
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }

   // check if top middle is available
   else if( initialRow > 0 && board[ initialRow - 1 ][ initialCol ].side != currentTurn )
      {
      
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow - 1, initialCol, currentType, currentTurn );
      
      // check if prjection puts out of check
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      // otherwise still in check, copy board
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }
        
   // check if top right is available
   else if( initialRow > 0 && initialCol < BOARD_SIZE - 1 && board[ initialRow - 1 ][ initialCol + 1 ].side != currentTurn )
      {
        
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow - 1, initialCol + 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }
        
   // check if left of king is available
   else if( initialCol > 0 && board[ initialRow ][ initialCol - 1 ].side != currentTurn )
      {
      
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow, initialCol - 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      else
         {
            
         copyBoard( checkedBoard, board );
         }
      }

   // check if right of king is available and won't put in check
   else if( initialCol < BOARD_SIZE - 1 && board[ initialRow ][ initialCol + 1 ].side != currentTurn )
      {

      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow, initialCol + 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }

   // check if bottom left is available and won't put in check
   else if( initialRow < BOARD_SIZE - 1 && initialCol > 0 && board[ initialRow + 1 ][ initialCol - 1 ].side != currentTurn )
      {
      
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow + 1, initialCol - 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
      
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }
        
   // check if bottom middle is available and won't put in check
   else if( initialRow < BOARD_SIZE - 1 && board[ initialRow + 1 ][ initialCol ].side != currentTurn )
      {
      
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow + 1, initialCol - 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }

      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }
      
  // check if bottom right is available and won't put in check
  else if( initialRow < BOARD_SIZE - 1 && initialCol < BOARD_SIZE - 1 && board[ initialRow + 1 ][ initialCol + 1 ].side != currentTurn )
      {
        
      // project moving the king
      pieceMoveHelper( checkedBoard, initialRow, initialCol, initialRow + 1, initialCol + 1, currentType, currentTurn );
      
      if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
         {
         
         return true;
         }
         
      else
         {
         
         copyBoard( checkedBoard, board );
         }
      }
   
   return false;
   }

/*
Description: checks all valid positions for the knight
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/
bool checkAllValidKnightPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode )
   {
   // initialize functions/variables
      // initialize current row/col variables
      int currentRow, currentCol;
   currentRow = rowIndex + 2;
   currentCol = colIndex + 1;

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
  
  
   currentRow = rowIndex + 2;
   currentCol = colIndex - 1;
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
      
   currentRow = rowIndex - 2;
   currentCol = colIndex + 1;
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
      
      
   currentRow = rowIndex + 2;
   currentCol = colIndex - 1;
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
      
   currentRow = rowIndex + 1;
   currentCol = colIndex + 2;
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
     
      
   currentRow = rowIndex - 1;
   currentCol = colIndex + 2;
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
      
   currentRow = rowIndex + 1;
   currentCol = colIndex - 2;
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
      
   currentRow = rowIndex - 1;
   currentCol = colIndex - 2;
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
      
   return false;
   }

/*
Description: checks if the current piece is on the leftmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/

bool checkAllValidPawnPositions( ChessBoardType **board, ChessBoardType **checkedBoard, char currentTurn, char currentType, int currentState, int initialRow, int initialCol, int currentCode )
	{

	// initialize functions/variables
		int currentRow = 0, currentCol = 0;

   if( currentTurn == 'P' )
		{

		currentRow = initialRow - 1;
      currentCol = initialCol - 1;
	   }

   else
      {

		currentRow = initialRow + 1;
      currentCol = initialCol + 1;
		}


	if( checkIfValidPosition( checkedBoard, currentType, currentTurn, initialRow, initialCol, currentRow, currentCol, &currentState, false ) )
		{
		
		if( currentCode == STALEMATE )
			{
			
			if( !putsOwnKingInCheck( board, currentTurn, initialRow, initialCol, currentRow, currentCol ) )
				{
				
				return true;
				}
			}
		// move piece and see if the board is still in check

		pieceMoveHelper( checkedBoard, initialRow, initialCol, currentRow, currentCol, currentType, currentTurn );

		if( !isInCheck( checkedBoard, currentTurn, INCHECK ) )
		   	{

			return true;
			}

		// reset the check board
		else
			{

			copyBoard( checkedBoard, board );
			}
		}

	return false;
	}
   
/*
Description: Checks every posible piece 
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/

bool checkAllValidRookPositions( ChessBoardType **board, ChessBoardType **checkedBoard, int checkRowIndex, int checkColIndex, int rowIndex, int colIndex, char currentType, char currentTurn, int initialRow, int initialCol, int currentState, int currentCode )
   {
   // initialize functions/variables
      // initialize current index variables to check all positions
      int currentRow, currentCol;
      
   // check every possible position for rook by incrementing current indexes
   for( checkRowIndex = rowIndex + 1; checkRowIndex < BOARD_SIZE; checkRowIndex++ )
      {

      currentRow = checkRowIndex;
      currentCol = colIndex;
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

   for( checkRowIndex = rowIndex - 1; checkRowIndex >= 0; checkRowIndex-- )
      {


      currentRow = checkRowIndex;
      currentCol = colIndex;
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

   for( checkColIndex = colIndex + 1; checkColIndex < BOARD_SIZE; checkColIndex++ )
      {

      currentRow = rowIndex;
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


   for( checkColIndex = colIndex - 1; checkColIndex >= 0; checkColIndex-- )
      {
  
      currentRow = rowIndex;
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

/*
Description: checks if the current piece is on the leftmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/

bool checkEdgePieceLeft( ChessBoardType **board, int currentCol )
   {
   return( currentCol == BOARD_SIZE - 1 );
   }

/*
Description: checks if the current piece is on the rightmost side of the board
Input: Current chess board, board row, board column
Output: the given chess piece type
Dependancies: NONE
*/

bool checkEdgePieceRight( ChessBoardType **board, int currentCol )
   {
   return( currentCol == 0 );
   }


