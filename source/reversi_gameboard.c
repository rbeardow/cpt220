/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gameboard.h"

/**
 * convenience array that you can use to print out the cell contents for 
 * each cell. It is in the same order as the cell_contents enumeration and 
 * if you pass the array element to printf it will print out the data 
 * including the color information.
 **/
const char * reversi_cell_strings[REVERSI_NUM_TOKEN_TYPES] = {
    " ", 
    ANSI_COLOR_BLUE "B" ANSI_COLOR_RESET,
    ANSI_COLOR_RED  "R" ANSI_COLOR_RESET
};

/**
 * The default startup board. You just need to copy this board (not copy
 * and paste, but with code) into the board passed in by 
 * reversi_gameboard_init(). Please note that copying and pasting the 
 * code for the board will get you 0 marks for board initialisation.
 **/
static const enum reversi_cell_contents start_board[REVERSI_BOARDHEIGHT][REVERSI_BOARDWIDTH] =
{
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_BLUE, CC_RED, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_RED, CC_BLUE, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    },
    { 
        CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, CC_EMPTY, 
        CC_EMPTY, CC_EMPTY, CC_EMPTY
    }
};

/**
 * simply copy the board defined above into the board (2d array) passed
 * into this function. 
 **/
void reversi_gameboard_init(
    enum reversi_cell_contents board[][REVERSI_BOARDWIDTH])
{
}

/**
 * Display the game board. You need to display the game board in the 
 * same format as shown in the assignment specification. 
 **/
void reversi_gameboard_display(
    enum reversi_cell_contents board[][REVERSI_BOARDWIDTH])
{
}

