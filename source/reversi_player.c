/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_player.h"
#include "reversi_gamerules.h"

static char * reversi_player_get_colour(enum reversi_cell_contents token)
{
    return token == CC_RED 
    ? ANSI_COLOR_RED "red" ANSI_COLOR_RESET
    : ANSI_COLOR_BLUE "blue" ANSI_COLOR_RESET;
}

/**
 * Initialise the player's data. You should prompt the user for their name,
 * set their token to CC_EMPTY and their score to 0.
 **/
enum input_result reversi_player_init(struct reversi_player* curplayer)
{
    char name[REVERSI_NAMELEN + REVERSI_EXTRACHARS];
    enum input_result result;
    memset(curplayer, 0, sizeof(struct reversi_player));
    while(result = read_string_from_keyboard("Please enter your name: ", 
        name, REVERSI_NAMELEN + REVERSI_EXTRACHARS), result == IR_FAILURE)
        ;
    if(result == IR_RTM)
    {
        return IR_RTM;
    }
    strcpy(curplayer->name, name);
    return IR_SUCCESS;
}

/**
 * Implements the player taking a move in the game. It starts by printing 
 * out the player's score (which you will need to calculate by calling 
 * the correct function) and their colour. You should then read in the
 * move coordinates and validate them (that there is two ints separated by 
 * a comma and no other input on the line). Then you should try to apply 
 * the move by calling the appropriate function in the game rules module.
 **/
enum input_result reversi_player_move(struct reversi_player* curplayer, 
    reversi_gameboard game_board)
{
    struct reversi_coordinate coords;
    enum input_result ir_result;
    reversi_player_calc_score(game_board, curplayer);
    printf("It is %s's turn and their colour is %s\n", curplayer->name, 
        reversi_player_get_colour(curplayer->token));
    printf("Their score is currently: %d\n", curplayer->score);
    while(ir_result = read_coordinates_from_keyboard(&coords), 
        ir_result == IR_FAILURE)
        ; /* do nothing */
    if(ir_result == IR_RTM)
    {
        return IR_RTM;
    }
    if(reversi_rules_applymove(game_board, curplayer, &coords))
    {
        return IR_SUCCESS;
    }
    else
    {
        return IR_FAILURE;
    }
}
