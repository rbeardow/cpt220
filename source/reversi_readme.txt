/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

Like the first assignment, this was a great and satisfying challenge.
Lots of hairy edge cases to think about, memory management design, IO,
arrays and linked lists. I felt the assignment spec was a little more ambigious
than assignment 1, but this may have been intentional so that we had to think
about things a bit more rather than it being prescriptive.

I agonised over a few things regarding the list implementation.

Firstly, whether or not the linked list should be restricted to MAX_NUM_SCORES
like the array list, or whether it should grow. This also affected how the scores 
file would be loaded too. In the end, I decided the scores file should be limited
to MAX_NUM_SCORES on read in both implementations, so that file load behaviour 
was the same in both.
However, in the linked list version I allowed the in memory list to grow, so if 
you had several games of reversi, the scoreboard was allowed to grow e.g. 11, 12 etc.
In the array list version, as discussed on the boards, when a new item is added
and the list is at capacity, the lowest score is dropped off and it's always maintained
at 10 items or below. I think this was a fair interpretation.

Nothing is perfect and of course style and formatting issues can be subjective, but 
overall I am reasonably happy with my implementation.










