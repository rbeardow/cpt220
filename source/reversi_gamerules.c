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

struct reversi_direction_result
{
    BOOLEAN success;
    enum reversi_cell_contents content;
};

/*
 * Peeks in the specified direction starting at coords. Populates peek
 * with the cell contents in that direction if returns true, otherwise
 * returns false if you've hit a board boundary.
 */
BOOLEAN reversi_step_direction(reversi_gameboard board,
                               const enum reversi_direction direction,
                               struct reversi_coordinate * coords,
                               enum reversi_cell_contents * contents)
{
    int test_x, test_y;
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

    if (test_x > 0 && 
        test_x <= REVERSI_BOARDWIDTH &&
        test_y > 0 &&
        test_y <= REVERSI_BOARDHEIGHT)
    {
        * contents = board[test_y - 1][test_x - 1];
        coords->x = test_x;
        coords->y = test_y;
        return TRUE;
    }
   
    return FALSE;

}

void reversi_update_cell(reversi_gameboard board,
                         const struct reversi_coordinate * coords,
                         const enum reversi_cell_contents content)
{
    board[coords->y - 1][coords->x - 1] = content;
}

/*
 * Attempts to capture all enemy pieces on the board in the specified direction
 * starting at the specified coords. If do_capture is FALSE, it is performed
 * as a dry run and the board is not updated (used for validation). If set
 * to TRUE, the board will be updated.
 */
BOOLEAN reversi_capture_direction(reversi_gameboard board,
                                  const enum reversi_direction direction,
                                  const struct reversi_coordinate * start,
                                  const enum reversi_cell_contents friend,
                                  const BOOLEAN do_capture)
{
    
    struct reversi_coordinate next_coords;
    enum reversi_cell_contents next_cell;
    enum reversi_cell_contents enemy;
    BOOLEAN enemy_found;
    BOOLEAN step_success;

    printf("Walking %d with start coords %d,%d\n", direction, start->x, start->y);

    next_coords.x = start->x;
    next_coords.y = start->y;
    enemy = (friend == CC_RED) ? CC_BLUE : CC_RED;
    enemy_found = FALSE;

    while (TRUE)
    {
        /*
        printf("In loop, with coords %d,%d\n", next_coords.x, next_coords.y);
        printf("Current cell is %d\n", next_cell);
        printf("Taking a step...");
        */
        step_success = reversi_step_direction(board, direction, &next_coords, &next_cell);
        /*
        printf("Step success? %d\n", step_success);
        printf("Step contents %d\n", next_cell);
        */
        if (step_success && next_cell != CC_EMPTY)
        {   
            printf("Hello\n");
            /* If the next cell is an enemy, we've found one and try capture */
            if (next_cell == enemy)
            {
                enemy_found = TRUE;
                if (do_capture)
                {
                    /* Mutate board */
                    printf("Capture!!\n");
                    reversi_update_cell(board, &next_coords, friend);
                }
            }
            /* We haven't found the enemy, invalid path. */
            else if (!enemy_found)
            {
                return FALSE;
            }
            /* We've found a terminating friendly, successful capture. */
            else
            {
                return TRUE;
            }
        }
        else 
        {
            return FALSE;
        }
    };

    return FALSE;
}


BOOLEAN reversi_validate_move(reversi_gameboard board,
                              const struct reversi_player * player,
                              const struct reversi_coordinate * coords)
{
    int dir;
    enum reversi_cell_contents cell_contents;
    enum reversi_cell_contents opposite_token;

    printf("Determining if valid move\n");

    cell_contents = board[coords->y - 1][coords->x - 1];

    printf("Current player is %d\n", player->token);
    opposite_token = player->token == CC_RED ? CC_BLUE : CC_RED;
    printf("Opposite is %d\n", opposite_token);

    if (cell_contents == CC_EMPTY)
    {
        printf("Cell is empty\n");
        /* Test each direction */
        for (dir = DIR_N; dir <= DIR_NW; dir++)
        {
            printf("Testing direction %d\n", dir);
            if (reversi_capture_direction(board, dir, coords, player->token, FALSE))
            {
                printf("Valid direction found, optimistically begin capture\n");
                reversi_capture_direction(board, dir, coords, player->token, TRUE);
                return TRUE;
            }
            else
            {
                printf("Invalid direction\n");
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
BOOLEAN reversi_rules_applymove(reversi_gameboard board, 
                                struct reversi_player * player,
                                const struct reversi_coordinate * coords)
{
    printf("Applying move at %d, %d\n", coords->x, coords->y);

    if (reversi_validate_move(board, player, coords))
    {
        reversi_update_cell(board, coords, player->token);
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