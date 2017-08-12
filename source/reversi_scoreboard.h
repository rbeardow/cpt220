/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include "reversi_shared.h"
#include "reversi_player.h"
#include "reversi_score.h"
#include "reversi_helpers.h"
#ifdef LinkedList
#include "reversi_linked_list.h"
#elif defined(ArrayList)
#include "reversi_array_list.h"
#else
#error You must specify LIST_TYPE as LinkedList or ArrayList.
#endif

#ifndef REVERSI_SCOREBOARD_H
#define REVERSI_SCOREBOARD_H

/*
 * Scoreboard display constants
 */
#define SCOREBOARD_PREFIX_LEN 2
#define SCOREBOARD_COL_LOSER 23
#define SCOREBOARD_COL_WINNER 25
#define SCOREBOARD_COL_SCORE 7
#define SCOREBOARD_WIDTH 55

/*
 * Main scoreboard structure
 */
struct reversi_scoreboard{
    struct reversi_list list;
    const char* fname;
};

/*
 * Enumeration of scores menu options
 */
enum reversi_scores_menu_option {
    SM_DEL, 
    SM_RESET, 
    SM_SAVE,
    SM_MM
};

/*
 * Initialises the scoreboard
 */
void reversi_scoreboard_init(struct reversi_scoreboard *);

/*
 * Clear the scoreboard, including freeing any memory allocated for scores
 * and file names
 */
void reversi_scoreboard_clear(struct reversi_scoreboard *);

/*
 * Add a score to the scoreboard
 */
BOOLEAN reversi_scoreboard_add(struct reversi_scoreboard *, 
                               const struct reversi_player_pair *);

/*
 * Handle delete option for the scoreboard
 */
void reversi_scoreboard_delete(struct reversi_scoreboard *);

/*
 * Handle reset option for the scoreboard
 */
void reversi_scoreboard_reset(struct reversi_scoreboard *);

/*
 * Renders the current scores in scoreboard format
 */
void reversi_scoreboard_display(struct reversi_scoreboard *);

/*
 * Displays the scoreboard menu
 */
void reversi_scoreboard_menu(struct reversi_scoreboard *);

/*
 * Handle save option for the scoreboard
 */
void reversi_scoreboard_save(struct reversi_scoreboard *);

#endif