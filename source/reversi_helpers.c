/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_helpers.h"


void print_repeat(char * msg, int times)
{
    int i;
    for (i = 0; i < times; i++)
    {
        printf(msg);
    }
}

void draw_underline(char * msg)
{
    int length = strlen(msg);
    printf("%s\n", msg);
    print_repeat(BANNER_CHAR, length);
    printf("\n");
}

int parse_pos_int(char * input)
{
    char * remaining;
    long result = strtol(input, &remaining, DECIMAL);
    if (result > 0) 
    {
        return result;
    }
    return PARSE_INT_FAILURE;
}

enum input_result request_string(char * msg, int length, char * string)
{
    char * input;
    input = malloc(length + REVERSI_EXTRACHARS);
    if (input == NULL)
    {
        exit(EXIT_FAILURE);
    }

    do
    {
        printf(msg);
        fgets(input, length + REVERSI_EXTRACHARS, stdin);
        if (input[strlen(input) - 1] != '\n')
        {
            printf("Error: input was too long.\n");
            read_rest_of_line();
        }
        else
        {
            break;
        }
    }
    while (TRUE);

    /*
     * Null terminate the input string from the user and copy it to the 
     * output variable.
     */
    input[strlen(input) - 1] = '\0';
    strcpy(string, input);
    free(input);

    return IR_SUCCESS;
}

/**
 * Required for correct buffer handling. If you detect buffer overflow
 * you should call this function. See the examples in 
 * ~e70949/shared/examples especially AdvIO and BasicIO
 **/
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
        ;
    clearerr(stdin);
}