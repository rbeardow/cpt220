/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include "reversi_shared.h"
#include "reversi_helpers.h"

#ifndef REVERSI_GAMEBOARD
#define REVERSI_GAMEBOARD

/* 
 * Defines for the size of the board 
 */
#define REVERSI_BOARDWIDTH 8
#define REVERSI_BOARDHEIGHT REVERSI_BOARDWIDTH

/* 
 * Needed for the width of each cell when displaying 
 */
#define REVERSI_CELLWIDTH 5

/* 
 * Constants for cell rendering 
 */
#define REVERSI_VERTICAL_CELL_CHAR "|"
#define REVERSI_HORIZONTAL_CELL_CHAR "-"

/* 
 * Colour constants for displaying the board 
 */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define REVERSI_NUM_TOKEN_TYPES 3

/* 
 * Valid string length for input coordinates 
 */
#define REVERSI_COORD_LEN 3

/* 
 * Enum which represents possible contents of each cell. 
 */
enum reversi_cell_contents 
{
    CC_EMPTY, CC_BLUE, CC_RED
};

/* 
 * Cell strings needed for displaying each value of empty, blue or red 
 */
extern const char * reversi_cell_strings[];

/* 
 * Cell strings that display the "long" name of each value e.g. "blue".
 * I know the requirements are for no global variables, but I think this
 * one is justified as a sibling of the above reversi_cell_strings.
 */
extern const char * reversi_cell_strings_long[];

/* 
 * The gameboard type 
 */
typedef enum reversi_cell_contents 
    reversi_gameboard[REVERSI_BOARDHEIGHT][REVERSI_BOARDWIDTH];

/* 
 * A coordinate in the system 
 */
struct reversi_coordinate 
{
    int x, y;
};

/* 
 * Init the gameboard to the starting state - just copy the provided board 
 */
void reversi_gameboard_init(reversi_gameboard);

/*
 * Render the gameboard to the screen.
 */
void reversi_gameboard_display(reversi_gameboard);

#endif