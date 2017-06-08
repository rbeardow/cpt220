/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #1 
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by Paul Miller
***********************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef SHARED_H
#define SHARED_H

/* definition of the BOOLEAN type. Note that enumerations start counting 
 * from 0 so here, FALSE has the value 0 and TRUE has the value 1. 
 * Please note that you cannot rely on true being 1 in C but rather 
 * true is a non-zero integer. For this reason you should not compare with
 * TRUE but rather with FALSE as that is reliably 0.
 */
typedef enum {
    FALSE, TRUE
} BOOLEAN;

/* the number of players in the game */
#define REVERSI_NUMPLAYERS 2

/* additional characters appended by fgets() */
#define REVERSI_EXTRACHARS 2

/* the maximum length of a line of output */
#define REVERSI_LINELEN 80

#endif
