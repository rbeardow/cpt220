/***********************************************************************
* CPT220 - Programming in C
* Study Period 2 2017 Assignment #2 
* Full Name        : Robert Ashton Beardow
* Student Number   : S3641721
* Start up code provided by Paul Miller
***********************************************************************/

#include "reversi_gamerules.h"

/**
 * These functions (reversi_rules_validmove_*) check that there is a valid
 * move in the direction specified. They simply grab the relevant 
 * coordinate(s) and move the counter in the direction of the intended
 * capture. If there is an enemy token there, we then iterate until we find
 * a friendly token. If we succeed there are some tokens to capture in the
 * direction specified and thus this is a valid move.
 **/
static BOOLEAN reversi_rules_validmove_north(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int captured = 0;

    --curr_y;
    if(curr_y < 0)
    {
        return FALSE;
    }
    while(curr_y > 0 && board[curr_y][coords->x] == othertok)
    {
        ++captured;
        --curr_y;
    }
    if(captured && board[curr_y][coords->x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_south(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int captured = 0;

    ++curr_y;
    if(curr_y >= REVERSI_BOARDHEIGHT)
    {
        return FALSE;
    }
    while(curr_y < REVERSI_BOARDHEIGHT - 1 
            && board[curr_y][coords->x] == othertok)
    {
        ++captured;
        ++curr_y;
    }

    if(captured && board[curr_y][coords->x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_east(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_x = coords->x;
    int captured = 0;

    --curr_x;
    if(curr_x < 0)
    {
        return FALSE;
    }
    while(curr_x > 0 && board[coords->y][curr_x] == othertok)
    {
        ++captured;
        --curr_x;
    }
    if(captured && board[coords->y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_west(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_x = coords->x;
    int captured = 0;

    ++curr_x;
    if(curr_x >= REVERSI_BOARDWIDTH)
    {
        return FALSE;
    }
    while(curr_x < REVERSI_BOARDWIDTH - 1 
            && board[coords->y][curr_x] == othertok)
    {
        ++captured;
        ++curr_x;
    }
    if(captured && board[coords->y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_southeast(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;
    int captured = 0;

    ++curr_y; 
    --curr_x;

    if(curr_y >= REVERSI_BOARDHEIGHT || curr_x < 0)
    {
        return FALSE;
    }

    while(curr_y < REVERSI_BOARDHEIGHT && curr_x > 0 
            && board[curr_y][curr_x] == othertok)
    {
        ++captured;
        ++curr_y;
        --curr_x;
    }
    if(captured && board[curr_y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_southwest(reversi_gameboard board, 
        enum reversi_cell_contents token, const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;
    int captured = 0;

    ++curr_y;
    ++curr_x;

    if(curr_y >= REVERSI_BOARDHEIGHT || curr_x >= REVERSI_BOARDWIDTH)
    {
        return FALSE;
    }

    while(curr_y < REVERSI_BOARDHEIGHT - 1 && 
            curr_x < REVERSI_BOARDWIDTH - 1 && 
            board[curr_y][curr_x] == othertok)
    {
        ++captured;
        ++curr_y;
        ++curr_x;
    }
    if(captured && board[curr_y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_northeast(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate* coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;
    int captured = 0;

    --curr_y;
    --curr_x;

    if(curr_y < 0 || curr_x < 0)
    {
        return FALSE;
    }

    while(curr_y > 0  && curr_x > 0 
            && board[curr_y][curr_x] == othertok)
    {
        ++captured;
        --curr_y;
        --curr_x;
    }
    if(captured && board[curr_y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN reversi_rules_validmove_northwest(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate* coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;
    int captured = 0;

    --curr_y;
    ++curr_x;

    if(curr_y < 0 || curr_x >= REVERSI_BOARDWIDTH)
    {
        return FALSE;
    }

    while(curr_y > 0 && curr_x < REVERSI_BOARDWIDTH - 1
            && board[curr_y][curr_x] == othertok)
    {
        ++captured;
        --curr_y;
        ++curr_x;
    }
    if(captured && board[curr_y][curr_x] == token)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * Tests if the location specified is a valid move for the token specified
 * on the board passed in. Firstly tests if the square is empty - we can't 
 * move a piece into a non-empty square. Next, it iterates over the possible
 * directions. If there is a valid move in that direction, add that direction
 * to the stack of directions so we only need to iterate over those later
 * and not directions where there is nothing to capture.
 **/
static BOOLEAN reversi_rules_validmove(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate* coords, 
        struct reversi_int_stack* direction_stack)
{
    enum reversi_direction dir;
    BOOLEAN success = FALSE;
    if(board[coords->y][coords->x] != CC_EMPTY)
    {
        return FALSE;
    }
    for(dir = RD_NORTH; dir < RD_INVALID; ++dir)
    {
        switch(dir)
        {
            case RD_NORTH:
                if(reversi_rules_validmove_north(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, RD_NORTH))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_SOUTH:
                if(reversi_rules_validmove_south(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, RD_SOUTH))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_EAST:
                if(reversi_rules_validmove_east(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, RD_EAST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_WEST:
                if(reversi_rules_validmove_west(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, RD_WEST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_NORTH_EAST:
                if(reversi_rules_validmove_northeast(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, 
                            RD_NORTH_EAST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_NORTH_WEST:
                if(reversi_rules_validmove_northwest(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, 
                            RD_NORTH_WEST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_SOUTH_WEST:
                if(reversi_rules_validmove_southwest(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack,
                            RD_SOUTH_WEST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            case RD_SOUTH_EAST:
                if(reversi_rules_validmove_southeast(board, token, coords))
                {
                    if(direction_stack)
                    {
                        if(!reversi_int_stack_push(direction_stack, 
                            RD_SOUTH_EAST))
                        {
                            fprintf(stderr, "Error: stack is full.\n");
                            return FALSE;
                        }
                    }
                    success = TRUE;
                }
                break;
            default: 
                /* if we get here, something very bad has gone wrong */
                assert(dir != RD_INVALID);
        }
    }
    return success;
}

/**
 * The following functions do the work of capturing the pieces. We
 * simply capture the values for the relevant coordinate(s) (either X or 
 * Y or perhaps both for a diagonal) and then iterate in the direction 
 * specified turning each enemy token we encounter into a friendly token and
 * finally we insert a friendly token at the coordinates passed in. Please
 * note that because we have already validated the move we don't need to 
 * do any validation checking at this stage.
 **/
static void reversi_capture_north(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    --curr_y;
    while(curr_y > 0 && board[curr_y][coords->x] == othertok)
    {
        board[curr_y--][coords->x] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_south(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    ++curr_y;
    while(curr_y < REVERSI_BOARDHEIGHT - 1 
        && board[curr_y][coords->x] == othertok)
    {
        board[curr_y++][coords->x] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_east(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_x = coords->x;
    --curr_x;
    while(curr_x > 0 && board[coords->y][curr_x] == othertok)
    {
        board[coords->y][curr_x--] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_west(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_x = coords->x;
    ++curr_x;
    while(curr_x < REVERSI_BOARDWIDTH - 1 
        && board[coords->y][curr_x] == othertok)
    {
        board[coords->y][curr_x++] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_north_east(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_x = coords->x;
    int curr_y = coords->y;

    --curr_y;
    --curr_x;
    while(curr_x > 0 && curr_y > 0 && board[curr_y][curr_x] == othertok)
    {
        board[curr_y--][curr_x--] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_north_west(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;

    --curr_y;
    ++curr_x;

    while(curr_x < REVERSI_BOARDWIDTH - 1 && curr_y > 0 
        && board[curr_y][curr_x] == othertok)
    {
        board[curr_y--][curr_x++] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_south_east(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;

    ++curr_y;
    --curr_x;

    while(curr_x > 0 && curr_y < REVERSI_BOARDHEIGHT - 1 
        && board[curr_y][curr_x] == othertok)
    {
        board[curr_y++][curr_x--] = token;
    }
    board[coords->y][coords->x] = token;
}

static void reversi_capture_south_west(reversi_gameboard board, 
        enum reversi_cell_contents token, 
        const struct reversi_coordinate * coords)
{
    enum reversi_cell_contents othertok = token == CC_RED ? CC_BLUE : CC_RED;
    int curr_y = coords->y;
    int curr_x = coords->x;

    ++curr_y;
    ++curr_x;

    while( curr_x < REVERSI_BOARDWIDTH - 1 && 
        curr_y < REVERSI_BOARDHEIGHT - 1
        && board[curr_y][curr_x] == othertok)
    {
        board[curr_y++][curr_x++] = token;
    }
    board[coords->y][coords->x] = token;
}

/**
 * This function actually applies a move. You should first test whether the
 * requested player move is valid (test all directions!) and then capture
 * all pieces in valid directions. If this is not a valid move, simply 
 * return FALSE.
 **/
BOOLEAN reversi_rules_applymove(reversi_gameboard board , 
        struct reversi_player * player, 
        const struct reversi_coordinate * coords)
{
    struct reversi_int_stack direction_stack;
    BOOLEAN success = FALSE;
    reversi_int_stack_init(&direction_stack);
    if(reversi_rules_validmove(board, player->token, coords, 
        &direction_stack))
    {
        enum reversi_direction dir;
        while(direction_stack.count > 0)
        {
            dir = reversi_int_stack_pop(&direction_stack);
            switch(dir)
            {
                case RD_NORTH:
                    reversi_capture_north(board, player->token, coords);
                    success = TRUE;
                    break;
                case RD_SOUTH:
                    reversi_capture_south(board, player->token, coords);
                    success = TRUE;
                    break;
                case RD_EAST:
                    reversi_capture_east(board, player->token, coords);
                    success = TRUE;
                    break;
                case RD_WEST:
                    reversi_capture_west(board, player->token, coords);
                    success = TRUE;
                    break;
                case RD_NORTH_EAST:
                    reversi_capture_north_east(board, player->token, 
                        coords);
                    success = TRUE;
                    break;
                case RD_NORTH_WEST:
                    reversi_capture_north_west(board, player->token, 
                        coords);
                    success = TRUE;
                    break;
                case RD_SOUTH_EAST:
                    reversi_capture_south_east(board, player->token, 
                        coords);
                    success = TRUE;
                    break;
                case RD_SOUTH_WEST:
                    reversi_capture_south_west(board, player->token, 
                        coords);
                    success = TRUE;
                    break;
                case RD_INVALID:
                    fprintf(stderr, "error: invalid direction in stack.\n");
                    return FALSE;
            }
        }
    }
    return success;
}

/**
 * Check if the current player has any move they can make. If they cannot, 
 * they have lost the game. 
 **/
BOOLEAN reversi_rules_gameover(reversi_gameboard board, 
        struct reversi_player * player)
{
    int xloc, yloc;
    if(reversi_gameboard_isfull(board))
    {
        return TRUE;
    }
    for(yloc = 0; yloc < REVERSI_BOARDHEIGHT; ++yloc)
    {
        for(xloc = 0; xloc < REVERSI_BOARDWIDTH; ++xloc)
        {
            struct reversi_coordinate coord;
            coord.x = xloc;
            coord.y = yloc;
            if(reversi_rules_validmove(board, player->token, &coord, NULL))
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/**
 * Iterate over the board and count the number of tokens that are the same
 * colour as the token of the player specified.
 **/
void reversi_player_calc_score(reversi_gameboard board, 
    struct reversi_player* player)
{
    enum reversi_cell_contents token = player->token;
    int curr_y, curr_x;
    int total_score = 0;

    for(curr_y = 0; curr_y < REVERSI_BOARDHEIGHT; ++curr_y)
    {
        for(curr_x = 0; curr_x < REVERSI_BOARDWIDTH; ++curr_x)
        {
            total_score += token == board[curr_y][curr_x];
        }
    }
    player->score = total_score;
}

/**
 * 
 **/
static struct reversi_player* max_player(struct reversi_player players[])
{
    struct reversi_player * max = NULL; 
    int count; 
    for(count = 0; count < REVERSI_NUMPLAYERS; ++count) 
    { 
        if(!max || max->score < players[count].score)
        { 
            max = &players[count];
        } 
    } 
    return max;
}

/**
 * gets the winner of the game. If the game is still in play this function
 * should return NULL and otherwise it should return the player with the
 * highest score.
 **/
struct reversi_player* reversi_rules_getwinner(reversi_gameboard board, 
    struct reversi_player players[])
{
    int count;
    BOOLEAN gameover = FALSE;
    for (count = 0; count < REVERSI_NUMPLAYERS; ++count)
    {

        if(reversi_rules_gameover(board, &players[count]))
        {
            gameover = TRUE;
        }
    }
    return gameover ? max_player(players) : NULL;
}
