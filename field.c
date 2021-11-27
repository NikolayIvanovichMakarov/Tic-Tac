#include "field.h"

//! Check N
#ifndef N
#define N 3
#elif N < 2
#error N is to low
#endif

size_t GET_SIZE()
{
	return (size_t)N;
}

TIC_TAC_BOOL
clean_tic_tac_field(TIC_TAC_FIELD field)
{
	size_t i;
	for (i = 0; i < GET_SIZE();++i)
	{
		free(field[i]);
	}
	free(field);
}

TIC_TAC_ERROR
fill_field_with_free_peace(TIC_TAC_FIELD field)
{
	size_t i,j;
	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
			field[i][j] = TIC_TAC_PIECE_FREE_PLACE;
		}
	}
	return TIC_TAC_ERROR_NO_PROBLEM;
}

TIC_TAC_ERROR
allocate_tic_tac_field(TIC_TAC_FIELD * p_field)
{
	size_t i,j;
	if (p_field == NULL)
		return TIC_TAC_ERROR_BROKEN_ARGS;
	
	//! Memorry allocation
	(*p_field) = (TIC_TAC_FIELD)malloc(sizeof(TIC_TAC_PIECE*) * GET_SIZE());
	if ((*p_field) == NULL)
		return TIC_TAC_ERROR_MEMORRY_PROBLEM;

	for (i = 0; i < GET_SIZE(); ++i)
	{
		(*p_field) [i] = (TIC_TAC_PIECE*)malloc(sizeof(TIC_TAC_PIECE) * GET_SIZE());
		if ((*p_field) [i] == NULL)
		{
			for (j = 0; j < i; ++j)
			{
				free((*p_field) [j]);
			}
			free((*p_field));
			return TIC_TAC_ERROR_MEMORRY_PROBLEM;
		}
	}
	return TIC_TAC_ERROR_NO_PROBLEM;
}

TIC_TAC_WINNER
tic_tac_get_winner(TIC_TAC_FIELD field)
{
	//! variables
	size_t i,j;
	TIC_TAC_BOOL fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;

	// check rows
	for (i = 0; (i < GET_SIZE()); ++i)
	{
		//! 
		if (field[i][0] == TIC_TAC_PIECE_FREE_PLACE)
			fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
		else
			fl_need_to_continue_search = TIC_TAC_BOOL_TRUE;

		//! 
		for (j = 1; fl_need_to_continue_search && (j < GET_SIZE()); ++j)
		{

			if (field[i][j-1] != field[i][j])
				fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
		}

		//! 
		if (fl_need_to_continue_search)
			return (TIC_TAC_WINNER)field[i][0];
	}

	//! check columns
	for (j = 0; (j < GET_SIZE()); ++j)
	{
		//!
		if (field[0][j] == TIC_TAC_PIECE_FREE_PLACE)
			fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
		else
			fl_need_to_continue_search = TIC_TAC_BOOL_TRUE;

		//! 
		for (i = 1; fl_need_to_continue_search && (i < GET_SIZE()); ++i)
		{

			if (field[i-1][j] != field[i][j])
				fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
		}

		//! 
		if (fl_need_to_continue_search)
		{
			return (TIC_TAC_WINNER)field[0][j];
		}
	}

	//! check cross left - right
	if (field[0][0] == TIC_TAC_PIECE_FREE_PLACE)
		fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
	else
		fl_need_to_continue_search = TIC_TAC_BOOL_TRUE;
	for (i = 1; fl_need_to_continue_search && (i < GET_SIZE()); ++i)
	{
		if (field[i][i] != field[i - 1][i - 1])
			fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
	}
	if (fl_need_to_continue_search)
		return (TIC_TAC_WINNER)field[0][0];

	//! check cross right - left
	if (field[0][GET_SIZE()-1] == TIC_TAC_PIECE_FREE_PLACE)
		fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
	else
		fl_need_to_continue_search = TIC_TAC_BOOL_TRUE;
	for (i = 1; fl_need_to_continue_search && (i < GET_SIZE()); ++i)
	{

		if (field[i][(GET_SIZE() - 1) - i] != field[i - 1][GET_SIZE() - i])
			fl_need_to_continue_search = TIC_TAC_BOOL_FALSE;
	}
	if (fl_need_to_continue_search)
		return (TIC_TAC_WINNER)field[0][GET_SIZE()-1];

	//! check for (free places)
	for (i = 0; i < GET_SIZE(); ++i)
	{
		for (j = 0; j < GET_SIZE(); ++j)
		{
			if (field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
				return TIC_TAC_WINNER_NO_WINNER;
		}
	}

	//! 
	return TIC_TAC_WINNER_FRIENDS_WIN;
}

TIC_TAC_ERROR 
init_tic_tac_field(TIC_TAC_FIELD * p_field)
{
	//! variables
	size_t i,j;
	TIC_TAC_ERROR error;
	
	if (p_field == NULL)
		return TIC_TAC_ERROR_BROKEN_ARGS;

	//! CHECK
	if ((*p_field) != NULL)
	{
		clean_tic_tac_field((*p_field));
	}

	error = allocate_tic_tac_field(p_field);
	
	if (error == TIC_TAC_ERROR_NO_PROBLEM)
	{
		return fill_field_with_free_peace((*p_field));
	}
	return error;
}

TIC_TAC_ERROR
set_piece(TIC_TAC_FIELD field, size_t pos_x, size_t pos_y, TIC_TAC_PIECE piece)
{
	if (field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
	{
		field[pos_y][pos_x] = piece;
		return TIC_TAC_ERROR_NO_PROBLEM;
	}
	
	return TIC_TAC_ERROR_NOT_EMPTY_PIECE;
}

TIC_TAC_BOOL
can_move(TIC_TAC_FIELD field, size_t pos_x, size_t pos_y)
{
	//! check correct pos 
	if ((pos_x >= GET_SIZE()) || (pos_y >= GET_SIZE()))
		return TIC_TAC_BOOL_FALSE;
	
	//! check free
	if (field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
		return TIC_TAC_BOOL_TRUE;
	else
		return TIC_TAC_BOOL_FALSE;

	//! return true	
	return TIC_TAC_BOOL_TRUE;
}