/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_shared.h"
#include "reversi_score.h"
#include "reversi_scoreboard.h"
#ifndef REVERSI_LOADER_H
#define REVERSI_LOADER_H
#ifdef LinkedList
#include "reversi_linked_list.h"
#elif defined(ArrayList)
#include "reversi_array_list.h"
#else
#error List Type Must Be Defined!
#endif
#include <stdio.h>
#include <errno.h>

#define REVERSI_SCORELEN 3
#define REVERSI_NUMCOMMAS 2
#define REVERSI_FILENAME_LEN 30
#define REVERSI_SCORE_LINE_LEN 44

/*
 * Validates and loads the data from the specified filename into the scoreboard
 */
BOOLEAN load_data(struct reversi_scoreboard *, const char *);

/*
 * Saves the data from the scoreboard to the specified filename
 */
BOOLEAN save_data(struct reversi_scoreboard *, const char *);

#endif