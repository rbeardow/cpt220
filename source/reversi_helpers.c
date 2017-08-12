/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_helpers.h"

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

/**
 * convenience function for reading a string from the keyboard
 **/
enum input_result read_string_from_keyboard(const char * prompt, 
    char * result, int len)
{
    printf("%s", prompt);
    /* read in the string */
    if(fgets(result, len, stdin) == NULL)
    {
        return IR_RTM;
    }
    /* check for a newline at the beginning of the string */
    if(*result == '\n')
    {
        return IR_RTM;
    }
    /* check for a newline existing in the string at all - if it is
       missing then there is left over input in the input buffer */
    if(result[strlen(result) - 1] != '\n')
    {
        fprintf(stderr, "Error: you entered to much input. "
            " Please try again.\n\n");
        read_rest_of_line();
        return IR_FAILURE;
    }
    /* remove the newline as it has served its purpose */
    result[strlen(result) - 1] = 0;
    return IR_SUCCESS;
}

/**
 * convenience function for reading an integer from the keyboard
 **/
enum input_result read_int_from_keyboard(const char * prompt, int * result)
{
    char str_result[NUMLEN + REVERSI_EXTRACHARS];
    enum input_result input_status;
    /* read a string from the keyboard */
    while(input_status = read_string_from_keyboard(prompt, str_result, 
        NUMLEN), input_status == IR_FAILURE)
        ;
    if(input_status == IR_RTM)
    {
        return IR_RTM;
    }
    /* convert to int */
    if(!strtoint(result, str_result))
    {
        return IR_FAILURE;
    }
    return IR_SUCCESS;
}

/**
 * converts string data to a coordinate pair
 **/
static BOOLEAN parse_coordinates( const char * move_string, 
    struct reversi_coordinate * coord)
{
    char * tok;
    char * copy = strdup(move_string);
    enum coord_position pos = 0;

    /* grab the first token */
    tok = strtok(copy, DELIMS);
    while(tok)
    {
        /* parse each token according to its position in the string -
           there should be two ints separated by a comma and each int
           should be between 1 and 8 */
        switch(pos)
        {
            case X:
                if(!strtoint(&coord->x, tok))
                {
                    free(copy);
                    return FALSE;
                }
                break;
            case Y:
                if(!strtoint(&coord->y, tok))
                {
                    free(copy);
                    return FALSE;
                }
                break;
            default:
                fprintf(stderr, "Error: invalid coordinate string.\n");
                return FALSE;
        }
        tok = strtok(NULL, DELIMS);
        ++pos;
    }
    /* check that there were exactly two tokens */
    if(--pos != Y)
    {
        fprintf(stderr, "Error: invalid coordinate string.\n");
        free(copy);
        return FALSE;
    }
    --coord->y;
    --coord->x;
    free(copy);
    return TRUE;
}

/**
 * reads a string from the keyboard and converts that string to a
 * coordinate pair 
 **/
enum input_result read_coordinates_from_keyboard(struct reversi_coordinate * result)
{
    char move_string[MOVE_STR_LEN + REVERSI_EXTRACHARS];
    enum input_result ir_result;
    struct reversi_coordinate coord;
    BOOLEAN success;
    /* read a string from the keyboard and handle any errors */
    do {
        while(ir_result = read_string_from_keyboard(
            "Please enter a move as a comma separated coordinate pair: ", 
            move_string, MOVE_STR_LEN + REVERSI_EXTRACHARS), ir_result
              == IR_FAILURE)
            ;
        /* handle ctrl-d and \n at the beginning of the line of input */
        if(ir_result == IR_RTM)
        {
            return IR_RTM;
        }
        /* parse the coordinate string into a coordinate pair */
        if(!parse_coordinates(move_string, &coord))
        {
            fprintf(stderr, "Error: invalid coordinates entered. "
                "Please try again.\n\n");
            success = FALSE;
            continue;
        }
        success = TRUE;
    } while (! success );
    *result = coord;
    return IR_SUCCESS;
}

/**
 * implementation of strdup that allocates space for a string and then
 * copies it. Note: a string returned from strdup must be freed by
 * calling the free() function. 
 **/
char * strdup(const char * orig)
{
    /* allocate space */
    char * copy = malloc(strlen(orig) + 1);
    if(!copy)
    {
        return NULL;
    }
    strcpy(copy, orig);
    return copy;
}

/**
 * takes in a source string and attempts to extract an integer which
 * is then returned via the "num" pointer
 **/
BOOLEAN strtoint(int * num, const char* source_string)
{
    char * end;
    /* try to extract a number from the string */
    long lresult = strtol(source_string, &end, DECIMAL);
    /* if there is whitespace at the end of the string, we ignore it */
    while(isspace(*end))
    {
        ++end;
    }
    /* if there is any trailing characters, then this is an invalid
       numeric string */
    if(*end)
    {
        fprintf(stderr, "Error: %s is not a valid integer.\n", source_string);
        return FALSE;
    }
    /* check that the number extracted is within the range of an int -
       strtol is designed to extract a long int which is much larger than
       an int 
    */
    if(lresult < INT_MIN || lresult > INT_MAX)
    {
        fprintf(stderr, "Error: %s is out of range for an int.\n", 
            source_string);
        return FALSE;
    }
    /* store the value for returning to the calling function */
    *num = lresult;
    return TRUE;
}

/**
 * The following functions implement a special data structure called a
 * stack which is basically an array where we remove the last elemente
 * added to the array. 
 **/

/**
 * initialise the stack data structure to be empty
 **/
void reversi_int_stack_init(struct reversi_int_stack* stack)
{
    memset(stack, 0, sizeof(struct reversi_int_stack));
}

/**
 * add an int to our stack. 
 **/
BOOLEAN reversi_int_stack_push(struct reversi_int_stack* stack, int data)
{
    if(stack->count >= REVERSI_MAX_STACK)
    {
        return FALSE;
    }
    /* do the adding - we increment the count of items so we always
       add to the stack in the correct location */
    stack->data[stack->count++]=data;
    return TRUE;
}

/**
 * return the last element added to the stack - note that here we do a
 * pre-increment because the array indexes are 0 based
 **/
int reversi_int_stack_pop(struct reversi_int_stack* stack)
{
    return stack->data[--stack->count];
}

/**
 * insert padding into the string on both the left and right
 * sides. Please note that we assume that output has at least inputlen
 * + 1 chars of space or you will have memory problems
 **/
void reversi_centre_string(char output[], const char input[], int inputlen)
{
    int padding = (inputlen - strlen(input))/2;
    sprintf(output, "%*c%s%*c", padding, ' ', input, padding, ' ');
}

/**
 * frees a dynamic array of token strings
 **/
void tokens_free(char ** tokens, int num_tokens)
{
    int count;
    for(count = 0; count < num_tokens; ++count)
    {
        free(tokens[count]);
    }
    free(tokens);
}

/**
 * The following functions manage a type called a string vector which
 * contains a dynamic array of strings and a count of how many
 * strings. This is more handy to use than a static 2d array.
 **/

/**
 * allocates space for a string_vector and initializes it to be an
 * empty vector.
 **/
struct string_vector * string_vector_make(void)
{
    /* allocate the vector object itself */
    struct string_vector * new = (struct string_vector*)
        malloc(sizeof(struct string_vector));
    if(!new)
    {
        perror("failed to allocate memory");
        return NULL;
    }
    /* initialize the string_vector to be empty */
    memset(new, 0, sizeof(struct string_vector));
    /* allocate space for the dynamic array of strings - starting at
       MIN_VECTOR_SIZE (a #define) - we will resize this if our needs
       grow beyond this size.
    */
    new->strings = (char **)malloc(sizeof(char*) * MIN_VECTOR_SIZE);
    if(!new->strings)
    {
        perror("failed to allocate memory");
        free(new);
        return NULL;
    }
    /* initialise the slots to be all empty */
    memset(new->strings, 0, sizeof(char*) * MIN_VECTOR_SIZE);
    new->num_slots = MIN_VECTOR_SIZE;
    return new;
}

/**
 * adds a string to our string vector. If we run out of space for
 * tokens it resizes the dynamic array by doubling its size
 **/
BOOLEAN string_vector_add(struct string_vector* vec, char* newstring)
{
    /* do we need to resize ? */
    if(vec->num_strings == vec->num_slots){
        /* double the size of the array */
        void * temp = realloc(vec->strings, 
            DOUBLE(vec->num_strings * sizeof(char*)));
        /* did our memory allocation succeed ? */
        if(!temp){
            perror("failed to reallocate memory");
            return FALSE;
        }
        vec->num_slots = DOUBLE(vec->num_slots);
        vec->strings = temp;
    }
    /* insert the new string */
    vec->strings[vec->num_strings++] = strdup(newstring);
    return TRUE;
}

/**
 * free the memory for our string vector
 **/
void string_vector_free(struct string_vector * vec)
{
    int count;
    /* iterate over the strings and free each one */
    for(count = 0; count < vec->num_strings; ++count){
        free(vec->strings[count]);
    }
    /* free the strings array itself */
    free(vec->strings);
    /* free the string vector itself as that was also allocated on the
       heap */
    free(vec);
}

/**
 * string tokenization function that uses the above defined
 * string_vector data structure.
 **/
struct string_vector * split_string(const char* orig, const char* delims)
{
    /* duplicate the string - we will have to free it later */
    char * copy = strdup(orig);
    struct string_vector * vec;
    char * tok;
    /* create the string_vector object that we will return later */
    vec = string_vector_make();
    /* begin tokenization */
    tok = strtok(copy, delims);
    while(tok){
        /* add each token to the string_vector */
        if(!string_vector_add(vec, tok)){
            string_vector_free(vec);
            free(vec);
        }
        tok = strtok(NULL, delims);
    }
    /* free the copy of the string we made earlier */
    free(copy);
    return vec;
}

/*
 * Convenience function to determine if string is positive confirm
 */
BOOLEAN is_confirmed(const char * confirm)
{
    return 
    (
        strcmp(confirm, REVERSI_CONFIRM_UPPER) == 0 || 
        strcmp(confirm, REVERSI_CONFIRM_LOWER) == 0
    );
}

/*
 * Convenience function to determine if string is positive reject
 */
BOOLEAN is_rejected(const char * confirm)
{
    return 
    (
        strcmp(confirm, REVERSI_REJECT_UPPER) == 0 || 
        strcmp(confirm, REVERSI_REJECT_LOWER) == 0
    );
}

/*
 * Convenience function which requires a positive confirm or reject
 */
BOOLEAN request_confirmation(const char * msg)
{
    enum input_result result;
    char confirm[REVERSI_CONFIRM_LEN + REVERSI_EXTRACHARS];
    do
    {
        result = read_string_from_keyboard(
            msg,
            confirm,
            REVERSI_CONFIRM_LEN + REVERSI_EXTRACHARS
        );
        if (result == IR_SUCCESS)
        {
            if (is_confirmed(confirm)) 
            {
                return TRUE;
            }
            else if (is_rejected(confirm))
            {
                return FALSE;
            }
        }
        result = IR_FAILURE;
    }
    while (result == IR_FAILURE);
    return FALSE;
}

/*
 * Attempts to centre the specified string 
 */
void print_center(const char * msg, int width)
{
    int diff = width - strlen(msg);
    int left_padding = diff == 1 ? 1 : diff / HALF_DIVISOR;
    int right_padding = (diff % MOD_EVEN == 0) ? left_padding - 1: left_padding;
    PRINT_REPEAT(' ', left_padding);
    printf("%s", msg);
    PRINT_REPEAT(' ', right_padding);
}