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
    reversi_gameboard board;
    struct reversi_player_pair result_pair;
    struct reversi_player * current_player = &players[0];
    struct reversi_player * other_player = &players[1];

    draw_underline("Welcome to Reversi");
    reversi_player_init(current_player);
    reversi_player_init(other_player);
    reversi_player_init_token(current_player, other_player);

    if (current_player->token != REVERSI_FIRST_PLAYER)
    {
        swap_players(&current_player, &other_player);
    }

    /*
    printf("Player 1 is %s with colour %d\n", current_player->name, current_player->token);
    printf("Player 2 is %s with colour %d\n", other_player->name, other_player->token);
    printf("Player 1 is %s with colour %d\n", current_player->name, current_player->token);
    printf("Player 2 is %s with colour %d\n", other_player->name, other_player->token);
    */

    /*
    swap_players(&current_player, &other_player);
    */
    
    reversi_gameboard_init(board);
    reversi_gameboard_display(board);




    /*
    reversi_gameboard board;
    */

    return result_pair;
}

