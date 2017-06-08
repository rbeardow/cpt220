/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "reversi_shared.h"
#include "reversi_gameboard.h"

#ifndef REVERSI_HELPERS_H
#define REVERSI_HELPERS_H

#define NUMLEN 20
#define DECIMAL 10
#define MOVE_STR_LEN 3
#define REVERSI_MAX_STACK 200
#define DELIMS ","

/* defines the possible values of an io request - it could fail, succeed
 * or there could be a request to return to the main menu
 */
enum input_result
{
    IR_FAILURE, IR_SUCCESS, IR_RTM
};

void read_rest_of_line(void);
#endif
