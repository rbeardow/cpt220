/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_scoreboard.h"
#include "reversi_io.h"

/*
 * Initialise the scoreboard list and file name 
 */
void reversi_scoreboard_init(struct reversi_scoreboard * scoreboard)
{
    reversi_list_init(&scoreboard->list);
    scoreboard->fname = NULL;
}

/*
 * Clears all rows from the scoreboard and frees the filename if necessary
 */
void reversi_scoreboard_clear(struct reversi_scoreboard * scoreboard)
{
    reversi_list_clear(&scoreboard->list);
    if (scoreboard->fname != NULL)
    {
        free((char *) scoreboard->fname);
    }
}

/* 
 * Adds the specified player pair result onto the scoreboard
 */
BOOLEAN reversi_scoreboard_add(struct reversi_scoreboard * scoreboard, 
                               const struct reversi_player_pair * players)
{
    struct reversi_score * score = malloc(sizeof(struct reversi_score));
    if (score == NULL)
    {
        fprintf(stderr, "Error: could not allocate memory for new score");
        return FALSE;
    }
    strcpy(score->winner, players->first->name);
    strcpy(score->loser, players->second->name);
    score->won_by = players->first->score - players->second->score;
    return reversi_list_add(&scoreboard->list, score);
}

/*
 * Handle delete menu option
 */
void reversi_scoreboard_delete(struct reversi_scoreboard * scoreboard)
{
    enum input_result result;
    int delete_index;
    int num_scores = reversi_list_size(&scoreboard->list);
    if (num_scores == 0)
    {
        return;
    }
    do
    {
        result = read_int_from_keyboard(
            "Please enter the entry number to delete (ctrl-d/enter on a new line to cancel): ", 
            &delete_index
        );
        if (result == IR_RTM)
        {
            return;
        }
        else if (result == IR_SUCCESS)
        {   
            if (delete_index > 0 && delete_index <= num_scores)
            {
                if (reversi_list_remove(&scoreboard->list, delete_index - 1))
                {
                    return;
                }
            }
            else
            {
                fprintf(stderr, "Error: please specify a valid scoreboard entry\n");
            }
        }
    }
    while (TRUE);
}

/*
 * Handle reset menu option
 */ 
void reversi_scoreboard_reset(struct reversi_scoreboard * scoreboard)
{
    enum input_result result;
    char confirm[REVERSI_CONFIRM_LEN + REVERSI_EXTRACHARS];
    do
    {
        result = read_string_from_keyboard(
            "Are you sure you want to delete all scores from the system (y/n):",
            confirm,
            REVERSI_CONFIRM_LEN + REVERSI_EXTRACHARS
        );
        if (result == IR_RTM)
        {
            return;
        }
        else if (result == IR_SUCCESS)
        {
            if (is_confirmed(confirm))
            {
                reversi_list_clear(&scoreboard->list);
            }
            return;
        }
    }
    while (TRUE);
}

/*
 * Handle save menu option
 */ 
void reversi_scoreboard_save(struct reversi_scoreboard * scoreboard)
{
    enum input_result result;
    char filename[REVERSI_FILENAME_LEN + REVERSI_EXTRACHARS];
    do
    {
        result = read_string_from_keyboard(
            "Please enter a new filename for these scores (ctrl-d or enter "
            "on an empty line to cancel): ", 
            filename,
            REVERSI_FILENAME_LEN + REVERSI_EXTRACHARS
        );
        if (
            result == IR_RTM ||
            (result == IR_SUCCESS && save_data(scoreboard, filename))
        )
        {
            return;
        }
    }
    while (TRUE);
}

/*
 * Handle display and input of the main scoreboard menu
 */
void reversi_scoreboard_menu(struct reversi_scoreboard * scoreboard)
{
    enum input_result result;
    char * prompt = "Please enter a choice: ";
    int menu_option = 0;
    BOOLEAN display_menu = TRUE;
    do
    {
        if (display_menu)
        {
            reversi_scoreboard_display(scoreboard);
            printf("Your options:\n");
            printf("-------------\n");
            printf("1) Delete a score from the scoreboard\n");
            printf("2) Reset the scoreboard to an empty board\n");
            printf("3) Save the scores to another filename\n");
            printf("4) Return to main menu\n");
            printf("Note: you can also press ctrl-d/enter to return to the main menu.\n");
        }
        result = read_int_from_keyboard(prompt, &menu_option);
        if (result == IR_RTM)
        {
            return;
        }
        else if (result == IR_SUCCESS)
        {   
            /* Offset for menu input */
            menu_option--;
            switch (menu_option)
            {
                /* Delete a score */
                case SM_DEL:
                    reversi_scoreboard_delete(scoreboard);
                    display_menu = TRUE;
                    break;
                /* Reset scoreboard */
                case SM_RESET:
                    reversi_scoreboard_reset(scoreboard);
                    display_menu = TRUE;
                    break;
                /* Save scores to file */
                case SM_SAVE:
                    reversi_scoreboard_save(scoreboard);
                    display_menu = TRUE;
                    break;
                /* Return to main menu */
                case SM_MM:
                    return;
                /* Invalid option selected */
                default:
                    display_menu = FALSE;
                    fprintf(stderr, "Error: %s\n", prompt);
            }
        }
    }
    while (TRUE);
}

/*
 * Render the current state of the scoreboard
 */
void reversi_scoreboard_display(struct reversi_scoreboard * scoreboard)
{
    int num_scores = reversi_list_size(&scoreboard->list);
    struct reversi_score * score;
    char prefix[SCOREBOARD_PREFIX_LEN + 1];
    int i;
    if (num_scores == 0)
    {
        printf("The scoreboard is currently empty.\n");
    }
    else
    {
        PRINT_HEADING("Reversi Scoreboard");
        PRINTLINE(SCOREBOARD_WIDTH);
        /*
         * The "winner" column in the sample binary was unbalanced, with 10 
         * padding spaces on the left and 8 on the right. In order to make this
         * the same as the sample, I've prefixed "winner" with a space.
         */
        print_center(" winner", SCOREBOARD_COL_WINNER);
        printf("|");
        print_center("loser", SCOREBOARD_COL_LOSER);
        printf("|");
        print_center("won by", SCOREBOARD_COL_SCORE);
        printf("\n");
        PRINTLINE(SCOREBOARD_WIDTH);

        /*
         * The performance of this loop will differ between list implementations.
         * Array list index access is obviously very fast, however for the 
         * linked list implementation access by index is more expensive. 
         * In this case I decided it's cleaner to access by index because we
         * don't want the implementation detail leaking out and our data sets 
         * are small.
         */
        for (i = 0; i < num_scores; i++)
        {
            score = reversi_list_get(&scoreboard->list, i);
            sprintf(prefix, "%d)", i + 1);
            printf("%s", prefix);
            print_center(score->winner, SCOREBOARD_COL_WINNER - strlen(prefix));
            printf("|");
            print_center(score->loser, SCOREBOARD_COL_LOSER);
            printf("|");
            printf(" %d", score->won_by);
            printf("\n");
        }
    }
    printf("\n");
}