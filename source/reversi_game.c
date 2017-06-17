/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_game.h"

/**
 * You need to swap the player pointers for the two pointers to pointers
 * passed in here. Note: this requires relatively little code but it does
 * require a good understanding of pointers. This is considered a HD 
 * requirement so there may be some of you who cannot figure this one out. 
 **/
static void swap_players(struct reversi_player ** lhs, 
                         struct reversi_player ** rhs)
{
    struct reversi_player * temp = * lhs;
    * lhs = * rhs;
    * rhs = temp;
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
    struct reversi_player_pair result_pair = {NULL, NULL};
    struct reversi_player * current_player = &players[0];   /* Eww?*/
    struct reversi_player * other_player = &players[1];
    enum input_result init_result;
    enum input_result move_result;
    BOOLEAN gameover;
    BOOLEAN quitting;

    draw_underline("Welcome to Reversi");

    /*
     * Initialise player 1.
     */
    do
    {
        init_result = reversi_player_init(current_player);
        if (init_result == IR_RTM && request_quit_menu())
        {   
            return result_pair;
        }
    }
    while (init_result != IR_SUCCESS);

    /*
     * Initialise player 2.
     */
    do
    {
        init_result = reversi_player_init(other_player);
        if (init_result == IR_RTM && request_quit_menu())
        {
            return result_pair;
        }
    }
    while (init_result != IR_SUCCESS);
    
    /*
     * Randomise players.
     */
    result_pair = reversi_random_start(players);

    /*
     * Initialise gameboard.
     */    
    reversi_gameboard_init(board);

    /*
     * Start main game loop.
     */
    gameover = FALSE;
    quitting = FALSE;
    move_result = IR_SUCCESS;
    while (!quitting && !gameover)
    {
        /* Test for gameover */
        if (FALSE)
        {
            gameover = TRUE;
            break;
        }

        reversi_gameboard_display(board);

        do
        {
            move_result = reversi_player_move(current_player, board);
            if (move_result == IR_RTM)
            {
                quitting = TRUE;
                break;
            }
        }
        while (move_result != IR_SUCCESS);
        
        swap_players(&current_player, &other_player);
        
    }

    if (gameover)
    {
        
    }
    else
    {
        result_pair.first = NULL;
        result_pair.second = NULL;
    }

    return result_pair;
}

struct reversi_player_pair reversi_random_start(struct reversi_player players[])
{
    /* Do random things */
    struct reversi_player_pair pair = {NULL, NULL};
    pair.first = &players[0];
    pair.second = &players[1];
    pair.first->token = CC_BLUE;
    pair.second->token = CC_RED;
    return pair;
}