/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_helpers.h"

#define BANNER_CHAR "-"

void draw_underline(char * msg)
{
    int length = strlen(msg);
    printf("%s\n", msg);
    draw_banner(length);
}

void draw_banner(int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf(BANNER_CHAR);
    }
    printf("\n");
}

BOOLEAN request_string(char * msg, int length, char * string)
{
    char * input;
    input = malloc(sizeof(char) * (length + REVERSI_EXTRACHARS));
    if (input == NULL)
    {
        exit(EXIT_FAILURE);
    }

    do
    {
        printf("%s", msg);
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

    strcpy(string, input);
    return TRUE;
}

/**
 * required for correct buffer handling. If you detect buffer overflow
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