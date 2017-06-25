/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gamerules.h"

/*
 * Convenience function to update the specified cell contents.
 * For consistency and readability.
 */
static void reversi_update_cell(reversi_gameboard board,
                         const struct reversi_coordinate * coords,
                         const enum reversi_cell_contents content)
{
    board[coords->y - 1][coords->x - 1] = content;
}

/*
 * Convenience function to retrieve the specified cell contents. 
 * For consistency and readability.
 */
static enum reversi_cell_contents reversi_get_cell(reversi_gameboard board,
                                            const struct reversi_coordinate * coords)
{
    return board[coords->y - 1][coords->x - 1];
}

/*
 * Attempts to take a step in the specified direction on the board based on
 * the starting coordinates in coords.
 * If the cell in the specified direction is valid (i.e. on the board) then
 * contents is populated with the contents of the cell, and coords is moved
 * to be the new cell coordinates.
 * This allows you to walk around the board in different directions and
 * test cell contents safely.
 */
static BOOLEAN reversi_step_direction(reversi_gameboard board,
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

/*
 * Attempts to capture all enemy pieces on the board in the specified direction
 * starting at the specified coords. If do_capture is FALSE, it is performed
 * as a dry run and the board is not updated (used for validation). If set
 * to TRUE, the board will be updated.
 */
static BOOLEAN reversi_walk_direction(reversi_gameboard board,
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

    next_coords.x = start->x;
    next_coords.y = start->y;
    enemy = (friend == CC_RED) ? CC_BLUE : CC_RED;
    enemy_found = FALSE;

    while (TRUE)
    {
        /* Take a step in the desired direction */
        step_success = reversi_step_direction
        (
            board, 
            direction, 
            &next_coords, 
            &next_cell
        );

        if (step_success && next_cell != CC_EMPTY)
        {   
            /* If the next cell is an enemy, we've found one and try capture */
            if (next_cell == enemy)
            {
                enemy_found = TRUE;
                if (do_capture)
                {
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
        /* Step failed (hit boundary) or next cell was empty */
        else 
        {
            return FALSE;
        }
    };

    return FALSE;
}

/* 
 * Tests the direction from start coords to see if it's valid.
 * Returns TRUE if the path is a valid capturable path.
 */
static BOOLEAN reversi_test_direction(reversi_gameboard board,
                                      const enum reversi_direction direction,
                                      const struct reversi_coordinate * start,
                                      const enum reversi_cell_contents friend)
{
    return reversi_walk_direction(board, direction, start, friend, FALSE);
}

/*
 * Captures enemy pieces in the specified direction from start coords.
 */
static BOOLEAN reversi_capture_direction(reversi_gameboard board,
                                  const enum reversi_direction direction,
                                  const struct reversi_coordinate * start,
                                  const enum reversi_cell_contents friend)
{
    return reversi_walk_direction(board, direction, start, friend, TRUE);
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

    int dir;
    BOOLEAN valid_move = FALSE;
    if (reversi_get_cell(board, coords) == CC_EMPTY)
    {
        /* Test each direction */
        for (dir = DIR_N; dir <= DIR_NW; dir++)
        {
            if (reversi_test_direction(board, dir, coords, player->token))
            {
                reversi_capture_direction(board, dir, coords, player->token);
                valid_move = TRUE;
            }
        }
    }

    if (valid_move)
    {
        reversi_update_cell(board, coords, player->token);
    }
    else
    {
        printf("Error: You have entered an invalid move. Please try again.\n");
    }
    
    return valid_move;
}

/*
 * Check if the current player has any move they can make. If they cannot, 
 * they have lost the game. 
 * Returns TRUE if the player CANNOT make a move i.e. TRUE if gameover.
 * 
 * This is simply implemented as a brute force check of all directions from all
 * empty cells. For now, this works - but it could be optimised.
 */
BOOLEAN reversi_rules_gameover(reversi_gameboard board, 
                               struct reversi_player * player)
{
    struct reversi_coordinate coords;
    int i, j, dir;
    for (i = 0; i < REVERSI_BOARDHEIGHT; i++) 
    {
        for (j = 0; j < REVERSI_BOARDWIDTH; j++) 
        {
            coords.y = i;
            coords.x = j;
            if (board[i][j] == CC_EMPTY)
            {
                for (dir = DIR_N; dir <= DIR_NW; dir++)
                {
                    if (reversi_test_direction(board, dir, &coords, player->token))
                    {
                        return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
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