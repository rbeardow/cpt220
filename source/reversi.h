/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "reversi_shared.h"
#include "reversi_player.h"
#include "reversi_game.h"
#include "reversi_scoreboard.h"
#include "reversi_helpers.h"
#include "reversi_io.h"
#ifdef LinkedList
#include "reversi_linked_list.h"
#elif defined(ArrayList)
#include "reversi_array_list.h"
#else
#error List Type is not defined!
#endif

#ifndef REVERSI_H
#define REVERSI_H

#define DEFAULT_ARG_COUNT 1
#define LOAD_ARG_COUNT 2
#define MAIN_MENU_INPUT_LEN 1

/*
 * Enumeration of main menu options
 */ 
enum reversi_main_menu_option {MM_PLAY, MM_SCORES, MM_EXIT};

/*
 * Handle display and capture of the main menu
 */
enum reversi_main_menu_option reversi_main_menu();

/*
 * Handle exit game confirmation
 */
BOOLEAN reversi_confirm_exit(struct reversi_scoreboard *);

#endif