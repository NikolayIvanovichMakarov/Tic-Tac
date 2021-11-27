#include <stdio.h>
#include <stdint.h>


#include "tic_tac_types.h"
#include "tic_tac_view_console.h"
#include "tic_tac_const_str_winners.h"
#include "field.h"

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