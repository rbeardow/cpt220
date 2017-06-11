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
 * Simply copy the board defined above into the board (2d array) passed
 * into this function. 
 **/
void reversi_gameboard_init(reversi_gameboard board)
{
    /* TODO: Investigate memcpy version */
    int i, j;
    for (i = 0; i < REVERSI_BOARDHEIGHT; i++) {
        for (j = 0; j < REVERSI_BOARDWIDTH; j++) {
            board[i][j] = start_board[i][j];
        }
    }
}

/**
 * Display the game board. You need to display the game board in the 
 * same format as shown in the assignment specification. 
 **/
void reversi_gameboard_display(reversi_gameboard board)
{

    int height = REVERSI_BOARDHEIGHT + 1;   /* Header row */
    int width = REVERSI_BOARDWIDTH + 2;     /* Leading and trailing cells */
    int cell_width;                         /* Calculated cell width */
    int i, j;                               /* Loop indicies */
    char row_index[NUMLEN];                 /* Row index as string */                  
    char column_index[NUMLEN];              /* Column index as string */
    enum reversi_cell_contents content;     /* Content of individual cell */

    BOOLEAN first_row;
    BOOLEAN first_column;
    BOOLEAN last_column;

    for (i = 0; i < height; i++)
    {
        /* Convert row index to string for display */
        snprintf(row_index, sizeof(row_index), "%d", i);

        for (j = 0; j < width; j++)
        {
            /* Convert column index to string for display */
            snprintf(column_index, sizeof(column_index), "%d", j);

            /* For convenience and clarity */
            first_row = (i == 0) ? TRUE : FALSE;
            first_column = (j == 0) ? TRUE : FALSE;
            last_column = (j == width - 1) ? TRUE : FALSE;

            /* First column has leading space, just to make it difficult */
            if (first_column)
            {
                cell_width = REVERSI_CELLWIDTH - 1;
            }
            /* Standard column */
            else 
            {
                cell_width = REVERSI_CELLWIDTH - 2;
            }

            /* Draw header row */
            if (first_row) 
            {   
                if (first_column || last_column)
                {
                    reversi_draw_cell("", cell_width, !last_column);
                }
                else
                {
                    reversi_draw_cell(column_index, cell_width, !last_column);
                }
            }
            /* Draw header column */
            else if (first_column)
            {
                reversi_draw_cell(row_index, cell_width, TRUE);
            }
            /* Draw trailing column */
            else if (last_column)
            {
                reversi_draw_cell("", cell_width, FALSE);
            }
            /* Draw cell based on board state */
            else
            {
                content = board[i][j];
                /*
                reversi_draw_cell(reversi_cell_strings[content], 
                                  cell_width, 
                                  !last_column);
                */
                if (content == CC_BLUE)
                {
                    reversi_draw_cell("B", cell_width, !last_column);
                }
                else if (content == CC_RED)
                {
                    reversi_draw_cell("R", cell_width, !last_column);
                }
                else 
                {
                    reversi_draw_cell("", cell_width, !last_column);
                }

            }
        }
        printf("\n");
        print_repeat(REVERSI_HORIZONTAL_CELL_CHAR,
                     REVERSI_BOARDWIDTH * REVERSI_CELLWIDTH);
        printf("\n");
    }

}

void reversi_draw_cell(const char * contents, int cell_width, BOOLEAN include_vert)
{
    int content_length;
    int padding_space;
    int pad_prefix;
    int pad_suffix;
    int i;

    content_length = strlen(contents);
    padding_space = cell_width - content_length;

    if (padding_space < 0){
        fprintf(stderr, "Cell width to small for content width.");
        exit(EXIT_FAILURE);
    }
    else if (padding_space % 2 == 0)
    {
        pad_prefix = (padding_space / 2);
        pad_suffix = pad_prefix;
    }
    else
    {
        pad_prefix = (padding_space + 1) / 2;
        pad_suffix = pad_prefix - 1;
    }
    
    for (i = 0; i < pad_prefix; i++)
    {
        printf(" ");
    }
    printf(contents);
    for (i = 0; i < pad_suffix; i++)
    {
        printf(" ");
    }

    if (include_vert)
    {
        printf(REVERSI_VERTICAL_CELL_CHAR);
    }
}