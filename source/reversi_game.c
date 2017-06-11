/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_game.h"

/**
 * you need to swap the player pointers for the two pointers to pointers
 * passed in here. Note: this requires relatively little code but it does
 * require a good understanding of pointers. This is considered a HD 
 * requirement so there may be some of you who cannot figure this one out. 
 **/
static void swap_players(struct reversi_player ** lhs, 
                         struct reversi_player ** rhs)
{
    struct reversi_player *temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

/**
 * implements the game loop for the game. Please see the assignment 
 * specification for the full discussion of the algorithm you need to 
 * implement here. 
 **/
struct reversi_player_pair reversi_play_game(struct reversi_player players[])
{
    /*int player_count;*/

    struct reversi_player * player1 = &players[0];
    struct reversi_player * player2 = &players[1];

    struct reversi_player_pair result_pair;
    struct reversi_player * current_player;
    struct reversi_player * other_player;

    draw_underline("Welcome to Reversi");

    /*
    player1 = malloc(sizeof(struct reversi_player));
    if (player1 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    player2 = malloc(sizeof(struct reversi_player));
    if (player2 == NULL) 
    {
        exit(EXIT_FAILURE);
    }
    */

    reversi_player_init(player1);
    reversi_player_init(player2);

    printf("Player 1 is %s", player1->name);
    printf("Player 2 is %s", player2->name);

    swap_players(&current_player, &other_player);


    /*
    reversi_gameboard board;
    */

    return result_pair;
}

