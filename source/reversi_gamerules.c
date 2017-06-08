/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gamerules.h"

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
    struct reversi_player* player)
{
}

