#include <stdio.h>
#include <stdint.h>


#include "tic_tac_types.h"
#include "tic_tac_view_console.h"
#include "tic_tac_const_str_winners.h"

//! Check N
#ifndef N
#define N 3
#elif N < 2
#error N is to low
#endif


//! FIELD SIZE
size_t GET_SIZE()
{
	return (size_t)N;
}

#define  GET_SIZE_X() GET_SIZE()
#define  GET_SIZE_Y() GET_SIZE()


//! Functional
TIC_TAC_BOOL
clean_tic_tac_field(TIC_TAC_PIECE ** p_field)
{
	//if (g_p_field != NULL)
	//{
		size_t i;
		for (i = 0; i < GET_SIZE_Y();++i)
		{
			free(p_field[i]);
		}
		free(p_field);
		p_field = NULL;
	//}
}

TIC_TAC_ERROR
fill_field_with_free_peace(TIC_TAC_PIECE * const * const p_field)
{
	//! Fill field with start value
	size_t i,j;
	for (i = 0; i < GET_SIZE_Y(); ++i)
	{
		for (j = 0; j < GET_SIZE_X(); ++j)
		{
			p_field[i][j] = TIC_TAC_PIECE_FREE_PLACE;
		}
	}
	return TIC_TAC_ERROR_NO_PROBLEM;
}

TIC_TAC_ERROR
allocate_tic_tac_field(TIC_TAC_PIECE *** p_field)
{
	size_t i,j;
	//! check p_field == NULL later
	//if (g_p_field == NULL )
	
	//! Memorry allocation
	(*p_field) = (TIC_TAC_PIECE**)malloc(sizeof(TIC_TAC_PIECE*) * GET_SIZE_X());
	if ((*p_field)  == NULL)
		return TIC_TAC_ERROR_MEMORRY_PROBLEM;

	for (i = 0; i < GET_SIZE_X(); ++i)
	{
		(*p_field) [i] = (TIC_TAC_PIECE*)malloc(sizeof(TIC_TAC_PIECE) * GET_SIZE_Y());
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
tic_tac_get_winner(TIC_TAC_PIECE * const * const p_field)
{
	//! variables
	size_t i,j;
	uint8_t fl_need_to_continue_search = 0;

	// check rows
	for (i = 0; (i < GET_SIZE_X()); ++i)
	{
		//!
		if (p_field[i][0] == TIC_TAC_PIECE_FREE_PLACE)
			fl_need_to_continue_search = 0;
		else
			fl_need_to_continue_search = 1;

		//!
		for (j = 1; (fl_need_to_continue_search == 1) && j < GET_SIZE_Y(); ++j)
		{

			if (p_field[i][j-1] != p_field[i][j])
				fl_need_to_continue_search = 0;
		}

		//! 
		if (fl_need_to_continue_search == 1)
			return (TIC_TAC_WINNER)p_field[i][0];
	}

	//! check columns
	for (j = 0; (j < GET_SIZE_Y()); ++j)
	{
		//!
		if (p_field[0][j] == TIC_TAC_PIECE_FREE_PLACE)
			fl_need_to_continue_search = 0;
		else
			fl_need_to_continue_search = 1;

		//!
		for (i = 1; (fl_need_to_continue_search == 1) && i < GET_SIZE_X(); ++i)
		{

			if (p_field[i-1][j] != p_field[i][j])
				fl_need_to_continue_search = 0;
		}

		//!
		if (fl_need_to_continue_search == 1)
		{
			return (TIC_TAC_WINNER)p_field[0][j];
		}
	}

	//! check cross left - right
	if (p_field[0][0] == TIC_TAC_PIECE_FREE_PLACE)
		fl_need_to_continue_search = 0;
	else
		fl_need_to_continue_search = 1;
	for (i = 1; (fl_need_to_continue_search == 1) &&  i < (GET_SIZE_X() ); ++i)
		if (p_field[i][i] != p_field[i - 1][i - 1])
			fl_need_to_continue_search = 0;
	if (fl_need_to_continue_search == 1)
		return (TIC_TAC_WINNER)p_field[0][0];

	//! check cross right - left
	if (p_field[0][GET_SIZE_X()-1] == TIC_TAC_PIECE_FREE_PLACE)
		fl_need_to_continue_search = 0;
	else
		fl_need_to_continue_search = 1;
	for (i = 1; (fl_need_to_continue_search == 1) &&  i < (GET_SIZE_X() ); ++i)
		if (p_field[i][(GET_SIZE_Y() - 1) - i] != p_field[i - 1][(GET_SIZE_Y() - 2) - i])
			fl_need_to_continue_search = 0;
	if (fl_need_to_continue_search == 1)
		return (TIC_TAC_WINNER)p_field[0][0];

	//! check for (free places)
	for (i = 0; i < GET_SIZE_X(); ++i)
	{
		for (j = 0; j < GET_SIZE_Y(); ++j)
		{
			if (p_field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
				return TIC_TAC_WINNER_NO_WINNER;
		}
	}

	//! 
	return TIC_TAC_WINNER_FRIENDS_WIN;
}

TIC_TAC_ERROR 
init_tic_tac_field(TIC_TAC_PIECE *** p_field)
{
	//! variables
	size_t i,j;
	TIC_TAC_ERROR error;
	
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
set_piece(TIC_TAC_PIECE * const * const p_field, const size_t pos_x, const size_t pos_y, const TIC_TAC_PIECE piece)
{
	if (p_field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
	{
		p_field[pos_y][pos_x] = piece;
		return TIC_TAC_ERROR_NO_PROBLEM;
	}
	
	return TIC_TAC_ERROR_NOT_EMPTY_PIECE;
}

TIC_TAC_BOOL
can_move(TIC_TAC_PIECE * const * const p_field, size_t pos_x, size_t pos_y)
{
	//! check correct
	if (pos_x >= GET_SIZE_X())
		return TIC_TAC_BOOL_FALSE;
	

	if (pos_y >= GET_SIZE_Y())
		return TIC_TAC_BOOL_FALSE;
	
	//! check free
	if (p_field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
		return TIC_TAC_BOOL_TRUE;
	else
		return TIC_TAC_BOOL_FALSE;

	//! return true	
	return TIC_TAC_BOOL_TRUE;
}

////////////////////////////////////
/////////////  players /////////////
////////////////////////////////////


////////////////////////////////////
//////////// game state ////////////
////////////////////////////////////

typedef enum
{
	e_ps_init = 0,
	e_ps_main_loop,
	e_ps_game_is_over,
} e_programm_state;

static e_programm_state g_s_cur_state = e_ps_init;

void
step(TIC_TAC_PIECE **p_field, TIC_TAC_PLAYER p_player)
{
	size_t x,y;
	int fl;
	int scan_fl;
	int ch;
	do
	{
		fl = 1;
		printf("\nNow step player <%s>\n",g_c_str_players[p_player]);
		printf("\nPlease, enter x and y ");
		
		scan_fl = scanf("%zu%zu",&x,&y);
		if (scan_fl == 2)
		{
			if (can_move(p_field, x,y) == TIC_TAC_BOOL_TRUE)
			{
				set_piece(p_field, x,y,p_player);
				fl = 0;
			}
		}
		else
		{
			while ((ch = fgetc(stdin)) != EOF) 
			{
				if (ch == '\n') 
					break;
  			}
		}
	} while(fl == 1);
}

void
change_player(TIC_TAC_PLAYER * p_player)
{
	if ((*p_player) == TIC_TAC_PLAYER_TIC)
		(*p_player) = TIC_TAC_PLAYER_TAC;
	else
		(*p_player) = TIC_TAC_PLAYER_TIC;
}

void
action_state(TIC_TAC_PIECE*** p_field, TIC_TAC_PLAYER *p_player)
{
	TIC_TAC_WINNER winner;
	switch(g_s_cur_state)
	{
		case e_ps_init:
			init_tic_tac_field(p_field);
			(*p_player) = TIC_TAC_PLAYER_TIC;
			view_field(*p_field, GET_SIZE(), GET_SIZE());
			change_state(e_ps_main_loop);
			break;
		case e_ps_main_loop:
			step(*p_field,*p_player);
			winner = tic_tac_get_winner(*p_field);
			view_field(*p_field, GET_SIZE(), GET_SIZE());
			if (winner == TIC_TAC_WINNER_NO_WINNER)
			{
				change_player(p_player);
			}
			else
			{
				printf("Winner is <%s>\n", g_c_str_winners[winner]);
				change_state(e_ps_game_is_over);
			}
			break;
		case e_ps_game_is_over:
			printf(" ======================\n");
			printf("||   Game is over     ||\n");
			printf(" ======================\n");
			break;
	}
}

void
change_state(e_programm_state e_ps_new_state)
{
	g_s_cur_state = e_ps_new_state;
	/*switch(e_ps_new_state)
	{
		case e_ps_init:
			g_s_cur_state = e_ps_;
			break;
		case e_ps_main_loop:
			g_s_cur_state = e_ps_main_loop;
			break;
		case e_ps_game_is_over:
			g_s_cur_state = e_ps_game_is_over;
			break;
	}*/
}


int
main(int argc, char **argv)
{
	TIC_TAC_PLAYER cur_player = TIC_TAC_PLAYER_NO;
	TIC_TAC_PIECE** p_field = NULL;

	//! Init
	g_s_cur_state = e_ps_init;

	while(g_s_cur_state != e_ps_game_is_over)
	{
		action_state(&p_field,&cur_player);
	};
	action_state(&p_field,&cur_player);

	return 0;
}