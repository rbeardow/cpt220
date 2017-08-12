/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_linked_list.h"
#include "reversi_scoreboard.h"

/**
 * you will need to come up with a reasonable set of function
 * prototypes for both the array_list and linked_list implementations
 * of the list. These functions must be the same in both as they will
 * be called from your other modules - the point here to understand is
 * that it should not matter which list type implementation is
 * used. The functions exposed to other sections of code should be the same.
 **/

void reversi_list_init(struct reversi_list * list)
{
    list->head = NULL;
    list->num_scores = 0;
}

struct reversi_score * reversi_list_get(struct reversi_list * list, int index)
{
    int i = 0;
    struct reversi_list_node * current = list->head;
    while (current != NULL)
    {
        if (i == index)
        {
            return current->data;
        }
        i++;
        current = current->next;
    }
    return NULL;
}

int reversi_list_size(struct reversi_list * list)
{
    return list->num_scores;
}

BOOLEAN reversi_list_add(struct reversi_list * list, struct reversi_score * item)
{
    struct reversi_list_node * current = list->head;
    struct reversi_list_node * new_node;

    new_node = malloc(sizeof(struct reversi_list_node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory for new list node");
        return FALSE;
    }
    new_node->data = item;
    new_node->next = current;

    if (current == NULL || item->won_by > current->data->won_by)
    {
        list->head = new_node;
    }
    else
    {
        while (current->next != NULL && current->next->data->won_by > item->won_by)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    list->num_scores++;
    return TRUE;
}

BOOLEAN reversi_list_remove(struct reversi_list * list, int index)
{
    int i = 0;
    struct reversi_list_node * current = list->head;
    struct reversi_list_node * previous = current;

    if (index > list->num_scores - 1)
    {
        fprintf(stderr, "Error: remove index is greater than list size");
        return FALSE;
    }

    if (index == 0)
    {
        list->head = current->next;
        free(current->data);
        free(current);
    }
    else
    {
        while (current != NULL)
        {
            if (i == index)
            {
                previous->next = current->next;
                free(current->data);
                free(current);
                break;
            }
            i++;
            previous = current;
            current = current->next;
        }
    }
    list->num_scores--;
    return TRUE;
}

void reversi_list_clear(struct reversi_list * list)
{
    struct reversi_list_node * current = list->head;
    struct reversi_list_node * next = NULL;
    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->num_scores = 0;
}