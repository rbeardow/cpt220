/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_array_list.h"


void reversi_list_init(struct reversi_list * list)
{
    list->num_scores = 0;
}

struct reversi_score * reversi_list_get(struct reversi_list * list, int index)
{
    return list->scores[index];
}

int reversi_list_size(struct reversi_list * list)
{
    return list->num_scores;
}

BOOLEAN reversi_list_add(struct reversi_list * list, struct reversi_score * item)
{
    int i;
    int insert_index = 0;
    int num_scores = list->num_scores;

    /* 
     * Determine insert position to ensure list is always sorted
     */
    for (i = 0; i < num_scores; i++)
    {
        if (item->won_by < list->scores[i]->won_by)
        {
            insert_index = i + 1;
        }
    }

    /*
     * If list is at capacity and the new insert position is in the range
     * drop the bottom score off the list
     */
    if (num_scores == MAX_NUM_SCORES)
    {
        /*
         * If the new score is still the lowest and we're at capacity,
         * it cannot be added but it is not a failure
         */
        if (insert_index > MAX_NUM_SCORES - 1)
        {
            return TRUE;
        }
        /*
         * Otherwise remove the last element to make room for the new insert
         */
        else
        {
            reversi_list_remove(list, num_scores - 1);
        }
    }

    /* 
     * Shuffle scores if necessary
     */
    if (insert_index < num_scores)
    {
        for (i = num_scores; i > insert_index; i--)
        {
            list->scores[i] = list->scores[i - 1];
        }
    }

    list->scores[insert_index] = item;
    list->num_scores++;
    return TRUE;
}

BOOLEAN reversi_list_remove(struct reversi_list * list, int index)
{
    int i;
    if (index >= list->num_scores)
    {
        fprintf(stderr, "Error: cannot remove score at index %d\n", index);
        return FALSE;
    }
    free(list->scores[index]);
    for (i = index; i < list->num_scores; i++)
    {
        list->scores[i] = list->scores[i + 1];
    }
    list->scores[list->num_scores - 1] = NULL;
    list->num_scores--;
    return TRUE;
}

void reversi_list_clear(struct reversi_list * list)
{
    int i;
    for (i = 0; i < list->num_scores; i++)
    {
        free(list->scores[i]);
    }
    list->num_scores = 0;
}