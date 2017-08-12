/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_shared.h"
#include "reversi_score.h"
#ifndef REVERSI_LINKED_LIST_H
#define REVERSI_LINKED_LIST_H

struct reversi_list_node
{
    struct reversi_score* data;
    struct reversi_list_node * next;
};

struct reversi_list
{
    struct reversi_list_node * head;
    size_t num_scores;
};

/*
 * Initialise the list.
 */
void reversi_list_init(struct reversi_list * list);

/*
 * Returns the score item at the specified index, or NULL if that index is invalid.
 */
struct reversi_score * reversi_list_get(struct reversi_list * list, int index);

/*
 * Returns the current size of the list.
 */
int reversi_list_size(struct reversi_list * list);

/*
 * Appends the item to the end of the current list. Returns FALSE if the list is full.
 */
BOOLEAN reversi_list_add(struct reversi_list * list, struct reversi_score * item);

/*
 * Removes the item at the specified index. Returns TRUE if the index was valid
 * and the item was sucessfully removed. Otherwise FALSE.
 */
BOOLEAN reversi_list_remove(struct reversi_list * list, int index);

/*
 * Clears and frees all list elements.
 */
void reversi_list_clear(struct reversi_list * list);

#endif