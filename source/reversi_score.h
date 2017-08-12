/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_shared.h"
#include "reversi_player.h"
#ifndef REVERSI_SCORE_H
#define REVERSI_SCORE_H

#define MAX_NUM_SCORES 10
#define REVERSI_SCORE_PARTS 3
#define REVERSI_SCORE_MIN 1
#define REVERSI_SCORE_MAX 64
#define REVERSI_SCORE_WON_BY_LEN 2
#define REVERSI_SCORE_WINNER_INDEX 0
#define REVERSI_SCORE_LOSER_INDEX 1
#define REVERSI_SCORE_WON_BY_INDEX 2

/*
 * Structure for an individual scoreboard entry
 */
struct reversi_score {
    char winner[REVERSI_NAMELEN + 1];
    char loser[REVERSI_NAMELEN + 1];
    int won_by;
};

/*
 * Parse a score from a specified string and return a new pointer to the
 * score structure. If validation fails, a NULL pointer is returned.
 */
struct reversi_score * reversi_score_parse(const char * score_data);

#endif