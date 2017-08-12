/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <time.h>
#include "reversi_shared.h"
#include "reversi_player.h"
#include "reversi_gamerules.h"
#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H
/* the position of the player object in the array */
enum player_position {
    FIRST_PLAYER, SECOND_PLAYER
};
/* implements the main game loop */
struct reversi_player_pair reversi_play_game(struct reversi_player[]);
/* randomises the game at startup */
struct reversi_player_pair reversi_random_start(struct reversi_player[]);
#endif
