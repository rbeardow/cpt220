/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi.h"

int main(int argc, char ** argv)
{
    enum reversi_main_menu_option option;
    struct reversi_player players[REVERSI_NUMPLAYERS];
    struct reversi_player_pair result_pair;
    struct reversi_scoreboard scores;

    /* 
     * Initialise the scoreboard
     */
    reversi_scoreboard_init(&scores);

    /* 
     * Verify correct number of command line args have been given and if 
     * necessary load the data from the file specified.
     */
    if (argc == LOAD_ARG_COUNT)
    {
        char * load_filename = argv[1];
        if (!load_data(&scores, load_filename))
        {
            return EXIT_FAILURE;
        }
    }
    else if (argc != DEFAULT_ARG_COUNT) 
    {
        fprintf(stderr, "Error: invalid arguments entered\n");
        fprintf(stderr, "Usage is reversi [filename]\n");
        return EXIT_FAILURE;
    }

    /* 
     * Main game menu loop 
     */
    do
    {
        option = reversi_main_menu();
        /* 
         * Play a game of Reversi
         */
        if (option == MM_PLAY)
        {
            result_pair = reversi_play_game(players);
            if (result_pair.first != NULL && result_pair.second != NULL)
            {
                if (!reversi_scoreboard_add(&scores, &result_pair)) {
                    return EXIT_FAILURE;
                }
            }
        }
        /* 
         * Display scoreboard menu 
         */
        else if (option == MM_SCORES)
        {
            reversi_scoreboard_menu(&scores);
        }
        /* 
         * Exit application 
         */
        else 
        {
            if (scores.fname != NULL)
            {
                if (!reversi_confirm_exit(&scores))
                {
                    return EXIT_FAILURE;
                }
            }
            reversi_scoreboard_clear(&scores);
            return EXIT_SUCCESS;
        }

    }
    while (TRUE);

}

/*
 * Handle confirmation on exit and saving scoreboard data if requested
 */
BOOLEAN reversi_confirm_exit(struct reversi_scoreboard * scoreboard)
{
    if (request_confirmation("Do you wish to save the scoreboard data? (y/n):"))
    {   
        return save_data(scoreboard, scoreboard->fname);
    }
    return TRUE;
}

/*
 * Handle display of the main menu.
 */
enum reversi_main_menu_option reversi_main_menu()
{
    enum input_result result;
    char * prompt = "Please enter a choice: ";
    int menu_option = 0;
    do
    {
        PRINT_HEADING("REVERSI");
        printf("1) Play a game\n");
        printf("2) Scores menu\n");
        printf("3) Exit the program\n");
        result = read_int_from_keyboard(prompt, &menu_option);
        if (result == IR_SUCCESS)
        {
            switch (menu_option)
            {
                case 1:
                    return MM_PLAY;
                case 2:
                    return MM_SCORES;
                case 3:
                    return MM_EXIT;
                default:
                    result = IR_FAILURE;
            }
        }
        fprintf(stderr, "Error: please make a valid selection\n");
    }
    while (result != IR_SUCCESS);
    return MM_EXIT;
}