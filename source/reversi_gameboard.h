/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include "reversi_shared.h"
#ifndef REVERSI_GAMEBOARD
#define REVERSI_GAMEBOARD
/* #defines for the size of the board */
#define REVERSI_BOARDWIDTH 8
#define REVERSI_BOARDHEIGHT REVERSI_BOARDWIDTH
/* needed for the width of each cell when displaying */
#define REVERSI_CELLWIDTH 5

/* colour constants for displaying the board */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define REVERSI_NUM_TOKEN_TYPES 3
enum reversi_cell_contents {
    CC_EMPTY, CC_BLUE, CC_RED
};

/* cell strings needed for displaying each value of empty, blue or red */
extern const char * reversi_cell_strings[];

/* the gameboard type */
typedef enum reversi_cell_contents 
    reversi_gameboard[REVERSI_BOARDHEIGHT][REVERSI_BOARDWIDTH];

/* a coordinate in the system */
struct reversi_coordinate{
    int x,y;
};
/* init the gameboard to the starting state - just copy the provided board */
void reversi_gameboard_init(reversi_gameboard);
void reversi_gameboard_display(reversi_gameboard);
/* is the gameboard full ? if so there's no possible moves */
BOOLEAN reversi_gameboard_isfull(reversi_gameboard);
#endif
