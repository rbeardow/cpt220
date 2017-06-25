/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <time.h>
#include "reversi_player.h"
#include "reversi_gamerules.h"
#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

/* 
 * Implements the main game loop.
 */
struct reversi_player_pair reversi_play_game(struct reversi_player[]);

/* 
 * Randomises the game at startup.
 */
struct reversi_player_pair reversi_random_start(struct reversi_player[]);

/*
 * Displays the game over details in the end of game scenario.
 */
void reversi_gameover_display(struct reversi_player_pair pair);

#endif