/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
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
static const enum reversi_cell_contents
start_board[REVERSI_BOARDHEIGHT][REVERSI_BOARDWIDTH] =
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
    memcpy(board, start_board, sizeof(start_board));
}

/**
 * print the heading for displaying the game board
 **/
static void reversi_gameboard_print_heading(void)
{
    int count;
    printf("    ");
    for(count = 0; count < REVERSI_BOARDWIDTH; ++count){
        printf ("| %d ", count + 1);
    }
    printf("|\n");
    PRINTLINE(REVERSI_BOARDWIDTH * REVERSI_CELLWIDTH);
}

/**
 * print a row of the game board - print the row number followed by
 * all the cells for that row
 **/
static void reversi_gameboard_printrow( enum reversi_cell_contents row[],
    int row_number)
{
    int count;
    printf("  %d |", row_number);
    for(count = 0; count < REVERSI_BOARDHEIGHT; ++count){
        printf(" %s |", reversi_cell_strings[row[count]]);
    }
    putchar('\n');
    PRINTLINE(REVERSI_BOARDWIDTH * REVERSI_CELLWIDTH);
}

/**
 * Display the game board. You need to display the game board in the 
 * same format as shown in the assignment specification. 
 **/
void reversi_gameboard_display(
    enum reversi_cell_contents board[][REVERSI_BOARDWIDTH])
{
    int ycount;
    reversi_gameboard_print_heading();
    for(ycount = 0; ycount < REVERSI_BOARDHEIGHT; ++ycount){
        reversi_gameboard_printrow(board[ycount], ycount + 1);
    }
}

/**
 * tests whether the game board is full. If the game board is full
 * then the game is over so we need to do no further work.
 **/
BOOLEAN reversi_gameboard_isfull(
    enum reversi_cell_contents board[][REVERSI_BOARDWIDTH])
{
    int x , y;
    for (y = 0; y < REVERSI_BOARDHEIGHT; ++y){
        for(x = 0; x < REVERSI_BOARDWIDTH; ++x){
            if(board[y][x] == CC_EMPTY){
                return FALSE;
            }
        }
    }
    return TRUE;
}
