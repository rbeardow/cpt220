/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gameboard.h"
#include "reversi_player.h"

#ifndef REVERSI_GAMERULES_H
#define REVERSI_GAMERULES_H

/* 
 * Required to be implemented as part of the assignment. 
 * See the assignment specification for further details.
 */
BOOLEAN reversi_rules_applymove(reversi_gameboard, 
                                struct reversi_player *,
                                const struct reversi_coordinate *);

/*
 * Determine whether the current player can make a valid move or not.
 */
BOOLEAN reversi_rules_gameover(reversi_gameboard, struct reversi_player *);

/*
 * Calculate the current score of the specified player.
 */
void reversi_player_calc_score(reversi_gameboard, struct reversi_player *);

#endif