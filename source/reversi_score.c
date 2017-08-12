/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_score.h"
#include "reversi_helpers.h"

/*
 * Parse and validate a score out of a string (e.g. from the input file).
 * Returns NULL if validation.
 */
struct reversi_score * reversi_score_parse(const char * score_data)
{
    struct reversi_score * score;
    struct string_vector * parts = split_string(score_data, DELIMS);
    BOOLEAN valid = TRUE;
    int won_by;

    if (parts->num_strings != REVERSI_SCORE_PARTS)
    {
        valid = FALSE;
        fprintf(stderr, "Error: score does not conform to format winner,loser,score\n");
    }
    else if (strlen(parts->strings[REVERSI_SCORE_WINNER_INDEX]) > REVERSI_NAMELEN) 
    {
        valid = FALSE;
        fprintf(stderr, "Error: winner name is larger than maximum length\n");
    }
    else if (strlen(parts->strings[REVERSI_SCORE_LOSER_INDEX]) > REVERSI_NAMELEN)
    {
        valid = FALSE;
        fprintf(stderr, "Error: loser name is larger than maximum length\n");
    }
    else if (strlen(parts->strings[REVERSI_SCORE_WON_BY_INDEX]) > REVERSI_SCORE_WON_BY_LEN) 
    {
        valid = FALSE;
        fprintf(stderr, "Error: score is larger than maximum length\n");
    }
    else
    {
        if (strtoint(&won_by, parts->strings[REVERSI_SCORE_WON_BY_INDEX]))
        {
            if (won_by < REVERSI_SCORE_MIN || won_by > REVERSI_SCORE_MAX)
            {
                valid = FALSE;
                fprintf(stderr, "Error: score is outside valid score range\n");
            }
        }
        else
        {
            valid = FALSE;
        }
    }

    if (!valid)
    {
        string_vector_free(parts);
        return NULL;
    }

    /* All valid, allocate score and copy values in */
    score = malloc(sizeof(struct reversi_score));
    if (!score) {
        fprintf(stderr, "Error: unable to allocate memory for reversi_score");
        return NULL;
    }
    strcpy(score->winner, parts->strings[REVERSI_SCORE_WINNER_INDEX]);
    strcpy(score->loser, parts->strings[REVERSI_SCORE_LOSER_INDEX]);
    score->won_by = won_by;
    string_vector_free(parts);
    return score;
}