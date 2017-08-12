/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_game.h"

/**
 * you need to swap the player pointers for the two pointers to pointers
 * passed in here. Note: this requires relatively little code but it does
 * require a good understanding of pointers. This is considered a HD 
 * requirement so there may be some of you who cannot figure this one out. 
 **/
static void swap_players(struct reversi_player ** lhs, 
			 struct reversi_player ** rhs)
{
	struct reversi_player * swapper = *lhs;
	*lhs = *rhs;
	*rhs = swapper;
}

/**
 * implements the game loop for the game. Please see the assignment 
 * specification for the full discussion of the algorithm you need to 
 * implement here. 
 **/
struct reversi_player_pair reversi_play_game(struct reversi_player players[])
{
	int player_count;
	struct reversi_player_pair result_pair, start_pair;
	struct reversi_player * current_player, *other_player;
	reversi_gameboard board;
	BOOLEAN game_over = FALSE;
	EMPTY_PAIR(result_pair);
	reversi_gameboard_init(board);
	for(player_count = 0; player_count < REVERSI_NUMPLAYERS; ++player_count)
	{
		if(reversi_player_init(players+player_count) == IR_RTM)
		{
			return result_pair;
		}
	}
	/* toss a coin for who will start first */
	start_pair = reversi_random_start(players);
	current_player = start_pair.first;
	other_player = start_pair.second;

        /* the main game loop */
	while(!game_over)
	{
		enum input_result result;
		reversi_gameboard_display(board);
                /* test for game over at the beginning of each turn -
                   no point having the turn if the player has no valid
                   moves
                */
		game_over = reversi_rules_gameover(board, current_player);
		if(game_over)
		{
			break;
		}
                /* allow the player to take their move */
		while(result = reversi_player_move(current_player, board), 
		      result == IR_FAILURE)
		{
			fprintf(stderr, "error: you have entered an invalid"
				" move. Please try again.\n\n");
		}
                /* if there is an early quit there is no winner */
		if(result == IR_RTM)
		{
			return result_pair;
		}
		swap_players(&current_player, &other_player);
	}
        /* if there was a winner, assign the values in the player pair
           so it can be returned to main() 
        */
	if(current_player->score != other_player->score)
	{
		if(current_player->score < other_player->score)
		{
			result_pair.first = other_player;
			result_pair.second = current_player;
		}
		else
		{
			result_pair.second = other_player;
			result_pair.first = current_player;
		}
	}
	printf("The winner was %s\n", result_pair.first->name);
	return result_pair;
}

/**
 * flip a coin to see who should start first
 **/
struct reversi_player_pair reversi_random_start(
	struct reversi_player players[])
{
	int rand_result;
	struct reversi_player_pair rand_pair;

        /* initialise the pair to be empty */
	EMPTY_PAIR(rand_pair);
	srand(time(NULL));
        /* do the coin flip */
	rand_result = rand() % REVERSI_NUMPLAYERS;
        /* initialiase the player pointers according to the result of
           the coin flip */
	rand_pair.first = &players[rand_result];
	rand_pair.second = &players[!rand_result];
	rand_pair.first->token = CC_BLUE;
	rand_pair.second->token = CC_RED;
	return rand_pair;
}
