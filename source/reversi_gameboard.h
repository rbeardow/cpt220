/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include "reversi_shared.h"
#include "reversi_helpers.h"

#ifndef REVERSI_GAMEBOARD
#define REVERSI_GAMEBOARD

/* Defines for the size of the board */
#define REVERSI_BOARDWIDTH 8
#define REVERSI_BOARDHEIGHT REVERSI_BOARDWIDTH

/* Needed for the width of each cell when displaying */
#define REVERSI_CELLWIDTH 5

#define REVERSI_VERTICAL_CELL_CHAR "|"
#define REVERSI_HORIZONTAL_CELL_CHAR "-"

/* Colour constants for displaying the board */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define REVERSI_NUM_TOKEN_TYPES 3

#define REVERSI_COORD_LEN 3

enum reversi_cell_contents {
    CC_EMPTY, CC_BLUE, CC_RED
};

/* cell strings needed for displaying each value of empty, blue or red */
extern const char * reversi_cell_strings[];

/* the gameboard type */
typedef enum reversi_cell_contents 
    reversi_gameboard[REVERSI_BOARDHEIGHT][REVERSI_BOARDWIDTH];

/* a coordinate in the system */
struct reversi_coordinate {
    int x, y;
};

/* init the gameboard to the starting state - just copy the provided board */
void reversi_gameboard_init(reversi_gameboard);

void reversi_gameboard_display(reversi_gameboard);

/*
 * Draw a gameboard cell.
 */
void reversi_draw_cell(const char *, int, BOOLEAN);

#endif
