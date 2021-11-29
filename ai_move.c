#include "tic_tac_types.h"
#include <stdint.h>
#include <stdlib.h>

//! 
TIC_TAC_BOOL 
ai_move_linear(TIC_TAC_FIELD field, TIC_TAC_PIECE ai_piece)
{
	size_t i,j;

	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
			if (field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
			{
				field[i][j] = ai_piece;
				return TIC_TAC_BOOL_TRUE;
			}
		}
	}
	return TIC_TAC_BOOL_FALSE;
}

//! 
TIC_TAC_BOOL 
ai_move_rand(TIC_TAC_FIELD field, TIC_TAC_PIECE ai_piece)
{
	size_t i,j;
	size_t free_piece_count = 0;
	size_t piece_rnd_pos;
	static TIC_TAC_BOOL s_b_initialize = TIC_TAC_BOOL_FALSE;
	
	//! step 0 initializing free count
	if (!s_b_initialize)
	{
		srand(time(NULL));
		s_b_initialize = TIC_TAC_BOOL_TRUE;
	}

	//! step 1 counting free places
	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
			if (field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
			{
				++free_piece_count;
			}
		}
	}

	//! step 2 generate round count from 0 to free_piece_count 
	piece_rnd_pos = rand() % free_piece_count;

	//! step 3 put piece into rnd free place
	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
			if (field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
			{
				if (piece_rnd_pos == 0)
				{
					field[i][j] = ai_piece;
					return TIC_TAC_BOOL_TRUE;
				}
				else
				{
					--piece_rnd_pos;
				}
			}
		}
	}
	
	return TIC_TAC_BOOL_FALSE;
}


TIC_TAC_BOOL ai_simple_algorithm(TIC_TAC_FIELD field, TIC_TAC_PIECE ai_piece)
{
	size_t i,j;

	//! step 0 searching first position, we can win with
	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
		}
	}

	return TIC_TAC_BOOL_TRUE;
}