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

/*
Description: compares every viable rook position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/

bool checkBishopPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState )
   {
   // initialize functions/variables
      int wkgRow, wkgCol;
      char oppositeSide = determineOppositeSide( currentTurn );

   // check up left of the rook starting one ahead
   for (wkgRow = initialRow - 1, wkgCol = initialCol - 1; wkgRow >= 0 && wkgCol >= 0; wkgRow--, wkgCol--)
      {
      if( *currentState == CHECK && board[ wkgRow ][ wkgCol ].type == KING && board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {
         
         return true;
         }

      // stop searching if a piece from the current turn is found
      if( board[ wkgRow ][ wkgCol ].side == currentTurn )
         {

         break;
         }

      // stop searching and report true if current positions match with search
      if( wkgRow == currentRow && wkgCol == currentCol )
         {

         return true;
         }

      // check if the current search index hits an opponent
      if( board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {

         // if this matches the current positions report true
         if( wkgRow == currentRow && wkgCol == currentCol )
            {
                
            return true;
            }

         break;
         }
      }

   // check up right of the rook starting one ahead
   for( wkgRow = initialRow - 1, wkgCol = initialCol + 1; wkgRow >= 0 && wkgCol < BOARD_SIZE; wkgRow--, wkgCol++ )
      {

      if( *currentState == CHECK && board[ wkgRow ][ wkgCol ].type == KING && board[ wkgRow ][ wkgCol ].side == oppositeSide )
        {
        
        return true;
        }

      // stop searching if a piece from the current turn is found
      if( board[ wkgRow ][ wkgCol ].side == currentTurn )
         {

         break;
         }

      // stop searching and report true if current positions match with search
      if( wkgRow == currentRow && wkgCol == currentCol )
         {

         return true;
         }

      // check if the current search index hits an opponent
      if( board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {

         // if this matches the current positions report true
         if( wkgRow == currentRow && wkgCol == currentCol )
            {

            return true;
            }

         break;
         }
      }

   // check up right of the rook starting one ahead
   for( wkgRow = initialRow + 1, wkgCol = initialCol + 1; wkgRow < BOARD_SIZE && wkgCol < BOARD_SIZE; wkgRow++, wkgCol++  )
      {

      if( *currentState == CHECK && board[ wkgRow ][ wkgCol ].type == KING && board[ wkgRow ][ wkgCol ].side == oppositeSide )
        {
        
        return true;
        }

      // stop searching if a piece from the current turn is found
      if( board[ wkgRow ][ wkgCol ].side == currentTurn )
         {

         break;
         }

      // stop searching and report true if current positions match with search
      if( wkgRow == currentRow && wkgCol == currentCol )
         {

         return true;
         }

      // check if the current search index hits an opponent
      if( board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {

         // if this matches the current positions report true
         if( wkgRow == currentRow && wkgCol == currentCol )
            {

            return true;
            }

         break;
         }
      }

   // check to the left of the rook starting one to the left
   for( wkgRow = initialRow + 1, wkgCol = initialCol - 1; wkgRow < BOARD_SIZE && wkgCol >= 0; wkgRow++, wkgCol-- )
      {

      if( *currentState == CHECK && board[ wkgRow ][ wkgCol ].type == KING && board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {

         return true;
         }
         
      // stop searching if a piece from the current turn is found
      if( board[ wkgRow ][ wkgCol ].side == currentTurn )
         {

         break;
         }

      // stop searching and report true if current positions match with search
      if( wkgRow == currentRow && wkgCol == currentCol )
         {

         return true;
         }

      // check if the current search index hits an opponent
      if( board[ wkgRow ][ wkgCol ].side == oppositeSide )
         {

         // if this matches the current positions report true
         if( wkgRow == currentRow && wkgCol == currentCol )
            {

            return true;
            }

         break;
         }
      }

   // if no positions match return false
   return false;
   }
   
/*
Description: checks available positions for king, only moves king if it doesn't put it in check
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/

bool checkKingPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState )
    { 

    // initialize functions/variables
    	int rooksInitialRow = 0, rooksInitialCol = 0, rooksCurrentCol = 0;

    // checking whether castle is possible
    	// checking if the current turn is 'player'
    if( currentTurn == 'P' )
        {
      	
        // check if the king is its original position and if the player is attempting castle
        if( initialRow == BOARD_SIZE - 1 && initialCol == BOARD_SIZE - 4 && ( ( currentRow == BOARD_SIZE - 1 && currentCol == BOARD_SIZE - 6 ) || ( *currentState == SELECTING ) ) )
            {
         
           // check if there is no obstructions to the left of the king
           if( board[ initialRow ][ initialCol - 1 ].type == NON_PLAYER && board[ initialRow ][ initialCol - 2 ].type == NON_PLAYER && board[ initialRow ][ initialCol - 3 ].type == NON_PLAYER )
               {
            
            // check if the rook or the king has moved
            if( board[ initialRow ][ initialCol ].hasMoved == false && board[ initialRow ][ initialCol - 4 ].hasMoved == false )
               {

               // determine whether the piece is being highlighted
               if( *currentState == MOVING )
               	   {
				   // dehighlight the king
               	   board[ initialRow ][ initialCol - 2 ].castlePos = false;

				   // move the rook and return true
	               rooksInitialRow = BOARD_SIZE - 1;
  	      	       rooksInitialCol = 0;
          		   rooksCurrentCol = BOARD_SIZE - 5;
               	   movePiece( board, currentTurn, rooksInitialRow, rooksCurrentCol, *currentState, rooksInitialRow, rooksInitialCol );
               	   }

               else if( *currentState == SELECTING )
               		{

               		board[ initialRow ][ initialCol - 2 ].castlePos = true;
               		}

		       return true;
               }
            }
        }
      
      // check if the king is its original position and if the player is attempting castle
      else if( initialRow == BOARD_SIZE - 1 && initialCol == BOARD_SIZE - 4 && ( ( currentRow == BOARD_SIZE - 1 && currentCol == BOARD_SIZE - 5 ) || ( *currentState == SELECTING ) ) )
        {
          
         // check if there is no obstructions to the right of the king
         if( board[ initialRow ][ initialCol + 1 ].type == NON_PLAYER && board[ initialRow ][ initialCol + 2 ].type == NON_PLAYER )
            {
            
            // check if the rook or king has moved
            if( board[ initialRow ][ initialCol ].hasMoved == false && board[ initialRow ][ initialCol + 3 ].hasMoved == false )
               {
                
                if( *currentState == MOVING )
                	{

                	// dehighlight the king
               	    board[ initialRow ][ initialCol + 2 ].castlePos = false;

		        	// move the rook and return true
                  rooksInitialRow = BOARD_SIZE - 1;
                	rooksInitialCol = BOARD_SIZE - 1;
                	rooksCurrentCol = BOARD_SIZE - 3;
                	movePiece( board, currentTurn, rooksInitialRow, rooksCurrentCol, *currentState, rooksInitialRow, rooksInitialCol );
                	}

                else if( *currentState == SELECTING )
                	{

                	board[ initialRow ][ initialCol + 2 ].castlePos = true;
                	}


                return true;
               }
            }
         }
      }

    // check if the current turn is 'opponent'
    if( currentTurn == 'O' )
        {
      	
        // check if the king is its original position and if the player is attempting castle
        if( initialRow == 0 && initialCol == BOARD_SIZE - 4 && ( ( currentRow == 0 && currentCol == BOARD_SIZE - 6 ) || ( *currentState == SELECTING ) ) )
            {
         
           // check if there is no obstructions to the left of the king
           if( board[ initialRow ][ initialCol - 1 ].type == NON_PLAYER && board[ initialRow ][ initialCol - 2 ].type == NON_PLAYER && board[ initialRow ][ initialCol - 3 ].type == NON_PLAYER )
               {
            
            // check if the rook or the king has moved
            if( board[ initialRow ][ initialCol ].hasMoved == false && board[ initialRow ][ initialCol - 4 ].hasMoved == false )
               {

               // determine whether the piece is being highlighted
               if( *currentState == MOVING )
               	   {

               	   // dehighlight the king
               	   board[ initialRow ][ initialCol - 2 ].castlePos = false;

				   // move the rook and return true
	               rooksInitialRow = 0;
  	      	       rooksInitialCol = 0;
          		   rooksCurrentCol = BOARD_SIZE - 5;
               	   movePiece( board, currentTurn, rooksInitialRow, rooksCurrentCol, *currentState, rooksInitialRow, rooksInitialCol );
               	   }

               else if( *currentState == SELECTING )
               		{

               		board[ initialRow ][ initialCol - 2 ].castlePos = true;
               		}

		       return true;
               }
            }
        }
      
      // check if the king is its original position and if the player is attempting castle
      else if( initialRow == 0 && initialCol == BOARD_SIZE - 4 && ( ( currentRow == 0 && currentCol == BOARD_SIZE - 5 ) || ( *currentState == SELECTING ) ) )
        {
          
        // check if there is no obstructions to the right of the king
        if( board[ initialRow ][ initialCol + 1 ].type == NON_PLAYER && board[ initialRow ][ initialCol + 2 ].type == NON_PLAYER )
            {
            
            // check if the rook or king has moved
            if( board[ initialRow ][ initialCol ].hasMoved == false && board[ initialRow ][ initialCol + 3 ].hasMoved == false )
               {
                
                if( *currentState == MOVING )
                	{
					// dehighlight the king
               	    board[ initialRow ][ initialCol + 2 ].castlePos = false;

		        	// move the rook and return true
               		rooksInitialRow = 0;
                	rooksInitialCol = BOARD_SIZE - 1;
                	rooksCurrentCol = BOARD_SIZE - 3;
                	movePiece( board, currentTurn, rooksInitialRow, rooksCurrentCol, *currentState, rooksInitialRow, rooksInitialCol );
                	}

                else if( *currentState == SELECTING )
                	{

                	board[ initialRow ][ initialCol + 2 ].castlePos = true;
                	}


                return true;
               }
            }
         }
      }

    // after checking the castling conditions, determine whether we are selecting or moving to move forward
    if( *currentState == SELECTING )
    	{

    	return true;
    	}

    // check if top left is available and won't put in check
    if( initialRow > 0 && initialCol > 0 && initialRow - 1 == currentRow && initialCol - 1 == currentCol && board[ initialRow - 1 ][ initialCol - 1 ].side != currentTurn )
        {
        
        return true;
        }

    // check if top middle is available and won't put in check
    if( initialRow > 0 && initialRow - 1 == currentRow && initialCol == currentCol && board[ initialRow - 1 ][ initialCol ].side != currentTurn )
        {
        
        return true;
        }
        
    // check if top right is available and won't put in check
    if( initialRow > 0 && initialCol < BOARD_SIZE - 1 && initialRow - 1 == currentRow && initialCol + 1 == currentCol && board[ initialRow - 1 ][ initialCol + 1 ].side != currentTurn )
        {
        
        return true;
        }
        
    // check if left of king is available and won't put in check
    if( initialCol > 0 && initialRow == currentRow && initialCol - 1 == currentCol && board[ initialRow ][ initialCol - 1 ].side != currentTurn )
        {
        
        return true;
        }

    // check if right of king is available and won't put in check
    if( initialCol < BOARD_SIZE - 1 && initialRow == currentRow && initialCol + 1 == currentCol && board[ initialRow ][ initialCol + 1 ].side != currentTurn )
        {
        
        return true;
        }

    // check if bottom left is available and won't put in check
    if( initialRow < BOARD_SIZE - 1 && initialCol > 0 && initialRow + 1 == currentRow && initialCol - 1 == currentCol && board[ initialRow + 1 ][ initialCol - 1 ].side != currentTurn )
        {
        
        return true;
        }
        
    // check if bottom middle is available and won't put in check
    if( initialRow < BOARD_SIZE - 1 && initialRow + 1 == currentRow && initialCol == currentCol && board[ initialRow + 1 ][ initialCol ].side != currentTurn )
        {
        
        return true;
        }
    // check if bottom right is available and won't put in check
    if( initialRow < BOARD_SIZE - 1 && initialCol < BOARD_SIZE - 1 && initialRow + 1 == currentRow && initialCol + 1 == currentCol && board[ initialRow + 1 ][ initialCol + 1 ].side != currentTurn )
        {
        
        return true;
        }

    // otherwise, return false
    return false;
    }

/*
Description: compares every viable knight position with current row
 and current collumn
Input: board, current row, current column
Output: the index from the given column
Dependancies: NONE
*/

bool checkKnightPositions( ChessBoardType **board, char currentTurn, int currentRow, int currentCol, int initialRow, int initialCol, int *currentState )
   {
   // initialize functions/variables
    char oppositeSide = determineOppositeSide( currentTurn );
    
   // checking upwards, only check if the piece is in the right position
      // check if initial row is 2 or greater
   if( initialRow > 1 )
      {
      // check if initial col is 1 or greater AND initial col is less than or equal to BOARD SIZE
      if( initialCol >= 0 && initialCol <= BOARD_SIZE - 1 )
         {
         
         // check conditions
         if( *currentState == CHECK && board[ initialRow - 2 ][ initialCol - 1 ].type == KING && board[ initialRow - 2  ][ initialCol - 1 ].side == oppositeSide )
            {
         
             return true;
            }

         // check upwards and to the left for given position for matching and non current turn
         if( initialRow - 2 == currentRow && initialCol - 1 == currentCol && board[ initialRow - 2 ][ initialCol - 1 ].side != currentTurn )
            {

            return true;
            }
         }

      // check if initial col is 6 or less AND initial col is greater than 0
      if( initialCol >= 0 && initialCol <= 6 )
         {
             
         if( *currentState == CHECK && board[ initialRow - 2 ][ initialCol + 1 ].type == KING && board[ initialRow - 2  ][ initialCol - 1 ].side == oppositeSide )
            {
         
             return true;
            }
            
         // check upwards and to the right for given position
         if( initialRow - 2 == currentRow && initialCol + 1 == currentCol && board[ initialRow - 2 ][ initialCol + 1 ].side != currentTurn )
            {

            return true;
            }
         }
      }

   // check downwards, only check if the piece is in the right position
   if( initialRow < 6 )
      {

      // check valid left down position
      if( initialCol >= 0 && initialCol <= BOARD_SIZE - 1 )
         {
             
         // check conditions
         if( *currentState == CHECK && board[ initialRow + 2 ][ initialCol - 1 ].type == KING && board[ initialRow + 2  ][ initialCol - 1 ].side == oppositeSide )
            {
         
             return true;
            }

         if( initialRow + 2 == currentRow && initialCol - 1 == currentCol && board[ initialRow + 2 ][ initialCol - 1 ].side != currentTurn )
            {

            return true;
            }
         }

      // check valid right down position
      if( initialCol >= 0 && initialCol <= 6 )
         {
         
         // check conditions
         if( *currentState == CHECK && board[ initialRow + 2 ][ initialCol + 1 ].type == KING && board[ initialRow + 2  ][ initialCol + 1 ].side == oppositeSide )
            {
         
             return true;
            }
            
         if( initialRow + 2 == currentRow && initialCol + 1 == currentCol && board[ initialRow + 2 ][ initialCol + 1 ].side != currentTurn )
            {

            return true;
            }
         }
      }
   
   // check right, only check if is in the right position
   if( initialCol < 6 )
      {
      
      // check right up position
      if( initialRow > 0 && initialRow <= BOARD_SIZE - 1 )
         {
         
         // check condtions
         if( *currentState == CHECK && board[ initialRow - 1 ][ initialCol + 2 ].type == KING && board[ initialRow - 1 ][ initialCol + 2 ].side == oppositeSide )
            {
         
             return true;
            }
         
         if( initialRow - 1 == currentRow && initialCol + 2 == currentCol && board[ initialRow - 1 ][ initialCol + 2 ].side != currentTurn )
            {
            
            return true;
            }
         }
      
      // check valid right down position
      if( initialRow < BOARD_SIZE - 1 && initialRow >= 0 )
         {
         
         // check conditions
         if( *currentState == CHECK && board[ initialRow + 1 ][ initialCol + 2 ].type == KING && board[ initialRow + 1  ][ initialCol + 2 ].side == oppositeSide )
            {
         
             return true;
            }
         
         if( initialRow + 1 == currentRow && initialCol + 2 == currentCol && board[ initialRow + 1 ][ initialCol + 2 ].side != currentTurn )
            {
            
            return true;
            }
         }
      }
   
   // check left, only check if is in the right position
   if( initialCol > 1 )
      {
      
      // check valid left up position
      if( initialRow > 0 && initialRow < BOARD_SIZE - 1 )
         {
         
         // check conditions
         if( *currentState == CHECK && board[ initialRow - 1 ][ initialCol - 2 ].type == KING && board[ initialRow - 1  ][ initialCol - 2 ].side == oppositeSide )
            {
         
             return true;
            }
         
         if( initialRow - 1 == currentRow && initialCol - 2 == currentCol && board[ initialRow - 1 ][ initialCol - 2 ].side != currentTurn )
            {
            
            return true;
            }
         }
         
      // check valid left down position
      if( initialRow < BOARD_SIZE - 1 && initialRow >= 0 )
         {
          
         if( *currentState == CHECK && board[ initialRow + 1 ][ initialCol - 2 ].type == KING && board[ initialRow + 1 ][ initialCol - 2 ].side == oppositeSide )
            {
         
             return true;
            }
            
         if( initialRow + 1 == currentRow && initialCol - 2 == currentCol && board[ initialRow + 1 ][ initialCol - 2 ].side != currentTurn )
            {
            
            return true;
            }
         }
      }

   return false;
   }




