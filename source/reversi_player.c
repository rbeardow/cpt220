/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_player.h"
#include "reversi_gamerules.h"

/**
 * Initialise the player's data. You should prompt the user for their name,
 * set their token to CC_EMPTY and their score to 0.
 **/
enum input_result reversi_player_init(struct reversi_player* curplayer)
{
    return IR_FAILURE;
}

/**
 * Implements the player taking a move in the game. It starts by printing 
 * out the player's score (which you will need to calculate by calling 
 * the correct function) and their colour. You should then read in the
 * move coordinates and validate them (that there is two ints separated by 
 * a comma and no other input on the line). Then you should try to apply 
 * the move by calling the appropriate function in the game rules module.
 **/
enum input_result reversi_player_move(struct reversi_player* curplayer, 
    reversi_gameboard game_board)
{
    return IR_FAILURE;
}
