/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi.h"

int main(void)
{
    /* will be required to be in main in assignment 2, so we'll put it here
     * from the get-go 
     */
    struct reversi_player players[REVERSI_NUMPLAYERS];
    reversi_play_game(players);

    return EXIT_SUCCESS;
}