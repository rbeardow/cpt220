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
static void swap_players(struct reversi_player ** player1, 
                         struct reversi_player ** player2)
{
    struct reversi_player * temp;
    temp = * player1;
    * player1 = * player2;
    * player2 = temp;
}

/*
 * Implements the game loop for the game. Please see the assignment 
 * specification for the full discussion of the algorithm you need to 
 * implement here.
 */
struct reversi_player_pair reversi_play_game(struct reversi_player players[])
{

    reversi_gameboard board;
    struct reversi_player_pair empty_pair;
    struct reversi_player_pair player_pair;
    struct reversi_player * current_player;
    struct reversi_player * other_player;
    enum input_result init_result;
    enum input_result move_result;

    draw_underline("Welcome to Reversi");

    /* Initialise player 1 */
    do
    {
        init_result = reversi_player_init(&players[0]);
        if (init_result == IR_RTM && request_quit_confirmation())
        {   
            return empty_pair;
        }
    }
    while (init_result != IR_SUCCESS);

    /* Initialise player 2 */
    do
    {
        init_result = reversi_player_init(&players[1]);
        if (init_result == IR_RTM && request_quit_confirmation())
        {
            return empty_pair;
        }
    }
    while (init_result != IR_SUCCESS);

    player_pair = reversi_random_start(players);
    current_player = player_pair.first;
    other_player = player_pair.second;

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

    struct reversi_player_pair pair;
    int first_index;
    int second_index;

    srand(time(NULL));
    if (rand() % 2 == 0)
    {
        first_index = 1;
        second_index = 0;
    }
    else
    {
        first_index = 0;
        second_index = 1;
    }

    pair.first = &players[first_index];
    pair.second = &players[second_index];
    pair.first->token = CC_BLUE;
    pair.second->token = CC_RED;
    return pair;
}

/*
 * Displays the game over details on the screen.
 */
void reversi_gameover_display(struct reversi_player_pair pair)
{
    int p1_total = pair.first->score;
    int p2_total = pair.second->score;
    struct reversi_player * winner;
    char * plural;
    int win_amount;

    if (p1_total != p2_total)
    {
        if (p1_total > p2_total)
        {
            winner = pair.first;
            win_amount = p1_total - p2_total;
        }
        else
        {
            winner = pair.second;
            win_amount = p2_total - p1_total;
        }
        plural = win_amount > 1 ? "s" : EMPTY_CHAR;
        printf(
            "The winner was %s and they won by %d point%s.\n", 
            winner->name, 
            win_amount, 
            plural
        );
    }
    else
    {
        printf("The game was a draw.\n");
    }
}