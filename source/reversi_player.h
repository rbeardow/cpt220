/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include "reversi_gameboard.h"
#include "reversi_helpers.h"

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H
#define REVERSI_NAMELEN 20
#define REVERSI_COORDLEN 3

/* 
 * Defines the first player colour 
 */
#define REVERSI_FIRST_PLAYER CC_BLUE

/*
 * Definition of the player's details. We need their name, their 
 * color (token) and the current number of tokens they have on the 
 * board (their score).
 */
struct reversi_player 
{
    char name[REVERSI_NAMELEN + 1];
    enum reversi_cell_contents token;
    int score;
};

/* 
 * At various places in the game, we need a player pair which what this
 * is provided for. At that point the usage of the pair will be explained.
 */
struct reversi_player_pair
{
    struct reversi_player * first;
    struct reversi_player * second;
};

/* 
 * Initialise the player. please see the relevant section of the assignment
 * specification on the initialisation of the player to see what you 
 * need to do here
 */
enum input_result reversi_player_init(struct reversi_player *);

/* 
 * Defines how a player's move is entered, validated and if it is a valid
 * move how the game board should be updated. Most of this should be done
 * by using other functions 
 */
enum input_result reversi_player_move(struct reversi_player *, 
                                      reversi_gameboard);

#endif