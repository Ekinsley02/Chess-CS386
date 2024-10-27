#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BOARD_SIZE 8
#define NON_PLAYER 'X'

typedef struct ChessBoardStruct
   {
      
    char type;
    char side;
    bool highlight;
    bool hasMoved;
    bool castlePos;
   } ChessBoardType;

// function prototypes

/*
Description: displays the entire chess board.
Input: given chess board
Output: printed chess board
Dependancies: NONE
*/
ChessBoardType **fillBoard( ChessBoardType **board );

/*
Description: Allocates memory for the chess board.
Input: number of rows and collumns
Output: allocated memory for the chess board
Dependancies: NONE
*/
ChessBoardType **initializeChessBoard();

/*
Description: Outputs the current board
Input: board
Output: board to terminal
Dependancies: NONE
*/
void outputBoard(ChessBoardType **board);

#endif