/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gameboard.h"

/*
 * convenience array that you can use to print out the cell contents for 
 * each cell. It is in the same order as the cell_contents enumeration and 
 * if you pass the array element to printf it will print out the data 
 * including the color information.
 */
const char * reversi_cell_strings[REVERSI_NUM_TOKEN_TYPES] = {
    " ", 
    ANSI_COLOR_BLUE "B" ANSI_COLOR_RESET,
    ANSI_COLOR_RED  "R" ANSI_COLOR_RESET
};

/*
 * Similar to reversi_cell_strings, this provides a mapping between the token
 * types and a longer "human readable" version of the token.
 */
 /*
const char * reversi_cell_strings_long[REVERSI_NUM_TOKEN_TYPES] = {
    " ", 
    ANSI_COLOR_BLUE "blue" ANSI_COLOR_RESET,
    ANSI_COLOR_RED  "red" ANSI_COLOR_RESET
};
*/
const char * reversi_cell_strings_long[REVERSI_NUM_TOKEN_TYPES] = {
    " ", 
    "blue",
    "red"
};

/*
 * The default startup board. You just need to copy this board (not copy
 * and paste, but with code) into the board passed in by 
 * reversi_gameboard_init(). Please note that copying and pasting the 
 * code for the board will get you 0 marks for board initialisation.
 */
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

/*
 * Draws a reversi gameboard cell of the specified width and contents. If
 * include_vert is TRUE the RHS vertical character is included.
 * Attempt to adjust the padding to fit the contents using cell_width.
 */
static void reversi_draw_cell(const char * contents, 
                              const int cell_width, 
                              const BOOLEAN include_vert)
{

    int padding_space;
    int pad_prefix;
    int pad_suffix;

    padding_space = cell_width - 1;

    if (padding_space < 0){
        fprintf(stderr, "Cell width too small for content width.");
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

    print_repeat(SPACE_CHAR, pad_prefix);
    printf(contents);
    print_repeat(SPACE_CHAR, pad_suffix);

    if (include_vert)
    {
        printf(REVERSI_VERTICAL_CELL_CHAR);
    }
}

/*
 * Simply copy the board defined above into the board (2d array) passed
 * into this function. 
 */
void reversi_gameboard_init(reversi_gameboard board)
{
    /* TODO: Investigate memcpy version */
    int i, j;
    for (i = 0; i < REVERSI_BOARDHEIGHT; i++) 
    {
        for (j = 0; j < REVERSI_BOARDWIDTH; j++) 
        {
            board[i][j] = start_board[i][j];
        }
    }
}

/*
 * Display the game board. You need to display the game board in the 
 * same format as shown in the assignment specification. 
 * 
 * This function is a little long for my liking, but the cognitative load
 * is low so I did not decompose it. 
 */
void reversi_gameboard_display(reversi_gameboard board)
{

    int height = REVERSI_BOARDHEIGHT + 1;   /* Header row */
    int width = REVERSI_BOARDWIDTH + 2;     /* Leading and trailing cells */
    int cell_width;                         /* Calculated cell width */
    char row_index[NUMLEN];                 /* Row index as string */                  
    char column_index[NUMLEN];              /* Column index as string */
    enum reversi_cell_contents content;     /* Content of individual cell */
    int i, j;                               /* Loop indicies */

    BOOLEAN first_row;
    BOOLEAN first_column;
    BOOLEAN last_column;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            /* Convert cell indicies to strings for display */
            sprintf(row_index, "%d", i);
            sprintf(column_index, "%d", j);

            /* For convenience and code readability */
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
                    reversi_draw_cell(SPACE_CHAR, cell_width, !last_column);
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
                reversi_draw_cell(SPACE_CHAR, cell_width, FALSE);
            }
            /* Draw cell based on board state */
            else
            {
                /* Offset for extra cells */
                content = board[i - 1][j - 1]; 
                /*
                reversi_draw_cell(
                    reversi_cell_strings[content], 
                    cell_width, 
                    !last_column
                );
                */
                /* This is for windows only */
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
                    reversi_draw_cell(SPACE_CHAR, cell_width, !last_column);
                }
            }
        }
        printf("\n");
        print_repeat
        (
            REVERSI_HORIZONTAL_CELL_CHAR,
            REVERSI_BOARDWIDTH * REVERSI_CELLWIDTH
        );
        printf("\n");
    }

}