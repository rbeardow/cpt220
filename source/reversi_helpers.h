/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "reversi_shared.h"

#ifndef REVERSI_HELPERS_H
#define REVERSI_HELPERS_H

#define NUMLEN 20
#define DECIMAL 10
#define MOVE_STR_LEN 3
#define REVERSI_MAX_STACK 200
#define DELIMS ","

/*
 * Useful characters and error codes.
 */
#define BANNER_CHAR "-"
#define SPACE_CHAR " "
#define EMPTY_CHAR ""
#define PARSE_INT_FAILURE -1
#define REVERSI_MENU_OPT_LEN 1

/* 
 * Defines the possible values of an io request - it could fail, succeed
 * or there could be a request to return to the main menu
 */
enum input_result
{
    IR_FAILURE, IR_SUCCESS, IR_RTM
};

/*
 * Helper function which provides a generic quit message. 
 * Returns TRUE if user confirms the quit, FALSE otherwise.
 * This is a BOOLEAN since on the quit menu an enter is considered the same
 * as a yes.
 */
BOOLEAN request_quit_confirmation();

/* 
 * Helper function to request a string from stdin.
 * No input (enter) and Ctrl+D are considered a return to menu request.
 */
enum input_result request_string(char * msg, int length, char * string);

/*
 * Helper function to print a character a specified number of times.
 */
void print_repeat(char *, int times);

/*
 * Helper function to print a message with an underline of the same length.
 */
void draw_underline(char * msg);

/*
 * Helper function to parse a positive integer out of a string.
 * Returns PARSE_INT_FAILURE on failure.
 */
int parse_pos_int(char * input);

void read_rest_of_line(void);

#endif