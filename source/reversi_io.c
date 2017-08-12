/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_io.h"

/*
 * Reads the specified file name and validates, parses, and allocates 
 * scores then adds them to the scoreboard.
 */
BOOLEAN load_data(struct reversi_scoreboard * scoreboard, const char * fname)
{
    FILE * scores_file;
    char contents[MAX_NUM_SCORES][REVERSI_SCORE_LINE_LEN + 1];
    char line[REVERSI_SCORE_LINE_LEN + REVERSI_EXTRACHARS];
    int line_count = 0;
    int i;

    if (strlen(fname) > REVERSI_FILENAME_LEN)
    {
        fprintf(stderr, "Error: scores file name is too long\n");
        return FALSE;
    }

    scores_file = fopen(fname, "r");
    if (scores_file == NULL && errno != ENOENT)
    {   
        perror("Error: unable to open scores file");
        return FALSE;
    }

    if (errno != ENOENT)
    {
        while (
            fgets(line, REVERSI_SCORE_LINE_LEN + REVERSI_EXTRACHARS, scores_file) != NULL
        )
        {
            if (line[strlen(line) -1] == '\n')
            {
                line[strlen(line) - 1] = 0;
            }
            strcpy(contents[line_count++], line);
            if (line_count > MAX_NUM_SCORES)
            {
                fclose(scores_file);
                fprintf(stderr, "Error: scores file has too many lines\n");
                return FALSE;
            }
        }
        fclose(scores_file);
        for (i = 0; i < line_count; i++)
        {
            struct reversi_score * score = reversi_score_parse(contents[i]);
            if (score != NULL)
            {
                reversi_list_add(&scoreboard->list, score);
            }
            else
            {
                fprintf(stderr, "Error: could not parse score on line %d\n", i + 1);
                reversi_list_clear(&scoreboard->list);
                return FALSE;
            }
        }
    }
    scoreboard->fname = strdup(fname);
    return TRUE;
}

/*
 * Saves the current state of the scoreboard to the specified file name
 */
BOOLEAN save_data(struct reversi_scoreboard * scoreboard, const char * fname)
{
    FILE * scores_file;
    struct reversi_score * score;
    int index;
    int num_scores = reversi_list_size(&scoreboard->list);

    scores_file = fopen(fname, "w");
    if (scores_file == NULL) {
        perror("Error: unable to write to file");
        return FALSE;
    }

    for (index = 0; index < num_scores; index++)
    {
        score = reversi_list_get(&scoreboard->list, index);
        fprintf(
            scores_file, 
            "%s,%s,%d\n",
            score->winner,
            score->loser,
            score->won_by
        );
    }
    fclose(scores_file);
    
    if (scoreboard->fname != NULL && strcmp(scoreboard->fname, fname) != 0)
    {
        free((char*) scoreboard->fname);
        scoreboard->fname = NULL;
    }
    if (scoreboard->fname == NULL)
    {
        scoreboard->fname = strdup(fname);
    }
    
    printf("File %s saved successfully\n", scoreboard->fname);
    return TRUE;
}