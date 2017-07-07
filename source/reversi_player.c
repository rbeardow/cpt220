/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <time.h>
#include <stdlib.h>
#include "reversi_player.h"
#include "reversi_gamerules.h"

static BOOLEAN reversi_is_valid_coord(int n)
{
    if (n > 0 && n <= REVERSI_BOARDWIDTH && n <= REVERSI_BOARDHEIGHT)
    {
        return TRUE;
    }
    return FALSE;
}

/*
 * Handles validation of an int input parameter for requesting a coordinate.
 */
static BOOLEAN reversi_validate_int(int n)
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

/*
 * Parses an input string into the specified coords structure and
 * handles validation.
 */
static BOOLEAN reversi_parse_coords(char * input,
                                    struct reversi_coordinate * coords)
{
    int x, y;
    char * result;
    int input_length = strlen(input);
    if (input_length == MOVE_STR_LEN)
    {
        result = strtok(input, DELIMS);
        if (result != NULL)
        {
            x = parse_pos_int(result);
            if (reversi_validate_int(x))
            {
                result = strtok(NULL, DELIMS);
                if (result != NULL)
                {
                    y = parse_pos_int(result);
                    if (reversi_validate_int(y))
                    {
                        coords->x = x;
                        coords->y = y;
                        return TRUE;
                    }
                }
            }
        }
        
    }
    else if (input_length > MOVE_STR_LEN) {
        printf("Error: coordinates entered are too long\n");
    }
    else if (input_length < MOVE_STR_LEN) {
        printf("Error: coordinates entered are too short\n");
    }
    return FALSE;
}

/*
 * Requests valid coordinates on the board.
 */
static enum input_result reversi_request_coords(struct reversi_coordinate * coords)
{
    char coords_input[MOVE_STR_LEN + 1];
    enum input_result coord_result;
    do
    {
        coord_result = request_string
        (
            "Please enter a move as a comma separated coordinate pair: ", 
            MOVE_STR_LEN, 
            coords_input
        );
        if (coord_result == IR_SUCCESS)
        {
            if (!reversi_parse_coords(coords_input, coords))
            {
                coord_result = IR_FAILURE;
            }
        }
    }
    while (coord_result == IR_FAILURE);
    return coord_result;
}

/*
 * Initialise the player's data. You should prompt the user for their name,
 * set their token to CC_EMPTY and their score to 0.
 */
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

    printf("It is %s's turn and their colour is %s\n", player->name, colour);
    printf("Their score is currently: %d\n", player->score); 

    do
    {
        coord_result = reversi_request_coords(&coords);
        if (coord_result == IR_SUCCESS)
        {
            if (!reversi_rules_applymove(board, player, &coords))
            {
                coord_result = IR_FAILURE;
            }
        }
    }
    while (coord_result == IR_FAILURE);
    return coord_result; 
}