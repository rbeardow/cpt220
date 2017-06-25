/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_game.h"

/**
 * You need to swap the player pointers for the two pointers to pointers
 * passed in here. Note: this requires relatively little code but it does
 * require a good understanding of pointers. This is considered a HD 
 * requirement so there may be some of you who cannot figure this one out. 
 */
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
 */
struct reversi_player_pair reversi_play_game(struct reversi_player players[])
{

    reversi_gameboard board;
    struct reversi_player_pair empty_pair = {NULL, NULL};
    struct reversi_player_pair player_pair;
    struct reversi_player * current_player = &players[0];
    struct reversi_player * other_player = &players[1];
    enum input_result init_result;
    enum input_result move_result;

    draw_underline("Welcome to Reversi");

    /* Initialise player 1 */
    do
    {
        init_result = reversi_player_init(current_player);
        if (init_result == IR_RTM && request_quit_confirmation())
        {   
            return empty_pair;
        }
    }
    while (init_result != IR_SUCCESS);

    /* Initialise player 2 */
    do
    {
        init_result = reversi_player_init(other_player);
        if (init_result == IR_RTM && request_quit_confirmation())
        {
            return empty_pair;
        }
    }
    while (init_result != IR_SUCCESS);

    player_pair = reversi_random_start(players);

    /* Initialise gameboard */    
    reversi_gameboard_init(board);

    /* Start main game loop */
    move_result = IR_SUCCESS;
    while (TRUE)
    {

        if (reversi_rules_gameover(board, current_player))
        {
            reversi_gameover_display(player_pair);
            break;
        }

        reversi_gameboard_display(board);

        do
        {
            move_result = reversi_player_move(current_player, board);
            if (move_result == IR_RTM && request_quit_confirmation())
            {
                return empty_pair;
            }
        }
        while (move_result != IR_SUCCESS);

        swap_players(&current_player, &other_player);
        
    }
    return player_pair;
}

/*
 * Randomises the colour of the specified players and ensures the blue player
 * is first.
 */
struct reversi_player_pair reversi_random_start(struct reversi_player players[])
{
    /* TODO: Randomise */
    struct reversi_player_pair pair = {NULL, NULL};
    pair.first = &players[0];
    pair.second = &players[1];
    pair.first->token = CC_BLUE;
    pair.second->token = CC_RED;
    return pair;
}

/*
 * Displays the game over details on the screen.
 */
void reversi_gameover_display(struct reversi_player_pair pair)
{
    printf("Game over.\n");
}