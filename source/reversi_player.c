/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include <time.h>
#include <stdlib.h>
#include "reversi_player.h"
#include "reversi_gamerules.h"

/**
 * Initialise the player's data. You should prompt the user for their name,
 * set their token to CC_EMPTY and their score to 0.
 **/
enum input_result reversi_player_init(struct reversi_player * player)
{
    char name[REVERSI_NAMELEN + 1];
    enum input_result result = request_string
    (
        "Please enter your name: ", 
        REVERSI_NAMELEN, 
        name
    );
    if (result == IR_SUCCESS) 
    {
        strcpy(player->name, name);
        player->score = REVERSI_INITIAL_SCORE;
        player->token = CC_EMPTY;
        return IR_SUCCESS;
    }
    return result;
}

/**
 * Implements the player taking a move in the game. It starts by printing 
 * out the player's score (which you will need to calculate by calling 
 * the correct function) and their colour. You should then read in the
 * move coordinates and validate them (that there is two ints separated by 
 * a comma and no other input on the line). Then you should try to apply 
 * the move by calling the appropriate function in the game rules module.
 **/
enum input_result reversi_player_move(struct reversi_player * player,
                                      reversi_gameboard board)
{
    const char * colour = reversi_cell_strings_long[player->token];
    struct reversi_coordinate coords;
    enum input_result coord_result;

    reversi_player_calc_score(board, player);
    printf("It is %s's turn and their colour is %s\n", player->name, colour);
    printf("Their score is currently: %d\n", player->score);

    coord_result = reversi_request_coords(&coords);
    if (coord_result == IR_SUCCESS)
    {
        if (!reversi_rules_applymove(board, player, &coords))
        {
            coord_result = IR_FAILURE;
        }
    }
    return coord_result; 
}


BOOLEAN reversi_is_valid_coord(int n)
{
    if (n > 0 && n <= REVERSI_BOARDWIDTH)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN reversi_validate_coord(int n)
{
    if (n == PARSE_INT_FAILURE)
    {
        printf("Error: please specify a valid integer\n");
        return FALSE;
    }
    else if (!reversi_is_valid_coord(n))
    {
        printf("Error: please specify a coordinate on the board\n");
        return FALSE;
    }
    return TRUE;
}

BOOLEAN reversi_parse_coords(char * input,
                             struct reversi_coordinate * coords)
{
    int x, y;
    char * result;
    int input_length = strlen(input);
    if (input_length == REVERSI_COORDLEN)
    {
        result = strtok(input, DELIMS);
        if (result != NULL)
        {
            x = parse_pos_int(result);
            if (reversi_validate_coord(x))
            {
                result = strtok(NULL, DELIMS);
                y = parse_pos_int(result);
                if (reversi_validate_coord(y))
                {
                    coords->x = x;
                    coords->y = y;
                    return TRUE;
                }
            }
        }
    }
    else if (input_length > REVERSI_COORDLEN) {
        printf("Error: coordinates entered are too long\n");
    }
    else if (input_length < REVERSI_COORDLEN) {
        printf("Error: coordinates entered are too short\n");
    }
    return FALSE;
}

enum input_result reversi_request_coords(struct reversi_coordinate * coords)
{
    char coords_input[REVERSI_COORD_LEN + 1];
    enum input_result coord_result;
    enum input_result result;
    do
    {
        coord_result = request_string
        (
            "Please enter a move as a comma separated coordinate pair: ", 
            REVERSI_COORD_LEN, 
            coords_input
        );
        if (coord_result == IR_SUCCESS && 
            reversi_parse_coords(coords_input, coords))
        {
            result = IR_SUCCESS;
        }
        else
        {
            result = IR_FAILURE;
        }

    }
    while (result == IR_FAILURE);
    return result;
}