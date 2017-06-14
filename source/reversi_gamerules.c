/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gamerules.h"

enum reversi_direction {
    DIR_N, DIR_NE, DIR_E, DIR_SE, DIR_S, DIR_SW, DIR_W, DIR_NW
};


BOOLEAN reversi_test_direction(reversi_gameboard board,
                               const enum reversi_direction direction,
                               const struct reversi_coordinate * coords,
                               const enum reversi_cell_contents test)
{
    int test_x, test_y;
    enum reversi_cell_contents found;

    switch (direction)
    {
        case DIR_N:
            test_x = coords->x;
            test_y = coords->y - 1;
            break;
        case DIR_NE:
            test_x = coords->x + 1;
            test_y = coords->y - 1;
            break;
        case DIR_E:
            test_x = coords->x + 1;
            test_y = coords->y;
            break;
        case DIR_SE:
            test_x = coords->x + 1;
            test_y = coords->y + 1;
            break;
        case DIR_S:
            test_x = coords->x;
            test_y = coords->y + 1;
            break;
        case DIR_SW:
            test_x = coords->x - 1;
            test_y = coords->y + 1;
            break;
        case DIR_W:
            test_x = coords->x - 1;
            test_y = coords->y;
            break;
        case DIR_NW:
            test_x = coords->x - 1;
            test_y = coords->y - 1;
            break;
        default:
            test_x = 0;
            test_y = 0;
    }

    printf("Testing logical coodinates %d, %d\n", test_x, test_y);
    printf("Testing for %d\n", test);

    /* Ensure boundaries are tested */
    if (test_x > 0 && 
        test_x <= REVERSI_BOARDWIDTH &&
        test_y > 0 &&
        test_y <= REVERSI_BOARDHEIGHT)
    {
        found = board[test_y - 1][test_x - 1];
        printf("Found %d\n", found);
        if (found == test)
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

BOOLEAN reversi_validate_move(reversi_gameboard board,
                              const struct reversi_player * player,
                              const struct reversi_coordinate * coords)
{
    int i;
    enum reversi_cell_contents target;
    enum reversi_cell_contents opposite;

    printf("Determining if valid move\n");

    target = board[coords->y - 1][coords->x - 1];

    printf("Current player is %d\n", player->token);
    opposite = player->token == CC_RED ? CC_BLUE : CC_RED;
    printf("Opposite is %d\n", opposite);

    if (target == CC_EMPTY)
    {
        printf("Cell is empty\n");
        /* Test each direction */
        for (i = DIR_N; i <= DIR_NW; i++)
        {
            printf("Testing %d\n", i);
            if (reversi_test_direction(board, i, coords, opposite))
            {
                printf("Successful move!");
                return TRUE;
            }
        }
    }
    printf("Error: You have entered an invalid move. Please try again.\n");
    return FALSE;
}

/**
 * This function actually applies a move. You should first test whether the
 * requested player move is valid (test all directions!) and then capture
 * all pieces in valid directions. If this is not a valid move, simply 
 * return FALSE.
 **/
BOOLEAN reversi_rules_applymove(reversi_gameboard board , 
                                struct reversi_player * player,
                                const struct reversi_coordinate * coords)
{
    printf("Applying move at %d, %d\n", coords->x, coords->y);

    if (reversi_validate_move(board, player, coords))
    {
        printf("Move was valid. Now capture.\n");
        return TRUE;
    }

    return FALSE;
}

/**
 * Check if the current player has any move they can make. If they cannot, 
 * they have lost the game. 
 **/
BOOLEAN reversi_rules_gameover(reversi_gameboard board, 
                               struct reversi_player * player)
{
    return FALSE;
}

/**
 * Iterate over the board and count the number of tokens that are the same
 * colour as the token of the player specified.
 **/
void reversi_player_calc_score(reversi_gameboard board, 
                               struct reversi_player * player)
{
    int i, j;
    int score = REVERSI_INITIAL_SCORE;
    for (i = 0; i < REVERSI_BOARDHEIGHT; i++)
    {
        for (j = 0; j < REVERSI_BOARDWIDTH; j++)
        {
            if (board[i][j] == player->token){
                score++;
            }
        }
    }
    player->score = score;
}