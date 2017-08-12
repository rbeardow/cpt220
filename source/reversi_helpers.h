/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
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
#include "reversi_gameboard.h"

#ifndef REVERSI_HELPERS_H
#define REVERSI_HELPERS_H

#define NUMLEN 20
#define DECIMAL 10
#define MOVE_STR_LEN 3
#define REVERSI_MAX_STACK 200
#define MIN_VECTOR_SIZE 20
#define DELIMS ","
#define DOUBLE(N) 2*(N)
#define HALF_DIVISOR 2
#define MOD_EVEN 2

#define REVERSI_CONFIRM_LEN 1
#define REVERSI_CONFIRM_UPPER "Y"
#define REVERSI_CONFIRM_LOWER "y"
#define REVERSI_REJECT_UPPER "N"
#define REVERSI_REJECT_LOWER "n"

/* defines the possible values of an io request - it could fail, succeed
 * or there could be a request to return to the main menu
 */
enum input_result
{
    IR_FAILURE, IR_SUCCESS, IR_RTM
};


/* is this an X or a Y coordinate ? */
enum coord_position
{
    X,Y
};

/* int stack type defined so we only have to iterate over the directions
 * where there is a valid capture
 */
struct reversi_int_stack
{
    int data[REVERSI_MAX_STACK];
    int count;
};

/* string_vector type used for string tokenization */
struct string_vector
{
    char ** strings;
    int num_slots;
    int num_strings;
};

/* functions for managing the string_vector type */
struct string_vector * string_vector_make(void);
BOOLEAN string_vector_add(struct string_vector*, char*);
void string_vector_free(struct string_vector *);
struct string_vector * split_string(const char*, const char*);

void read_rest_of_line(void);

/* functions for reading from the keyboard */
enum input_result read_string_from_keyboard(const char*, char*, int);
enum input_result read_int_from_keyboard(const char*, int*);
enum input_result read_coordinates_from_keyboard(struct reversi_coordinate* );

/* helper function for converting from string to an integer as that's a 
 * common need
 */
BOOLEAN strtoint(int *, const char*);
/* make a copy of a string. Please note that any functions that call this
 * function have the responsibility to free it later 
 */
char * strdup(const char *);

/* int stack manipulation functions */
void reversi_int_stack_init(struct reversi_int_stack*);
BOOLEAN reversi_int_stack_push(struct reversi_int_stack*, int);
int reversi_int_stack_pop(struct reversi_int_stack*);

/* helper function to centre a string in a given output char array */
void reversi_centre_string(char [], const char[], int);

/*
 * Convenience function to determine if string is positive confirm
 */
BOOLEAN is_confirmed(const char * confirm);

/*
 * Convenience function to determine if string is positive reject
 */
BOOLEAN is_rejected(const char * confirm);

/*
 * Convenience function which requires a positive confirm or reject
 */
BOOLEAN request_confirmation(const char * msg);

/*
 * Attempts to centre the specified string 
 */
void print_center(const char * msg, int width);

#endif
