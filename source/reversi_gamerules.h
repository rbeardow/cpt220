/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_shared.h"
#include "reversi_gameboard.h"
#include "reversi_player.h"

/**
 * defines the various directions that a capture may happen in.
 **/
enum reversi_direction
{
    RD_NORTH, RD_SOUTH, RD_EAST, RD_WEST, RD_NORTH_EAST, RD_SOUTH_EAST, 
    RD_NORTH_WEST, RD_SOUTH_WEST, RD_INVALID
};

/** 
 * required to be implemented as part of the assignment. See the assignment
 * specification for further details
 **/
BOOLEAN reversi_rules_applymove(reversi_gameboard, struct reversi_player *,
    const struct reversi_coordinate*);

BOOLEAN reversi_rules_gameover(reversi_gameboard, 
    struct reversi_player *);

struct reversi_player * reversi_rules_getwinner(reversi_gameboard, 
    struct reversi_player[]);

void reversi_player_calc_score(reversi_gameboard, struct reversi_player*);

