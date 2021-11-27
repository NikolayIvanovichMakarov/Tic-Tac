#ifndef FIELD_H
#define FIELD_H

#include "tic_tac_types.h"


//! \brief размер поля 
size_t GET_SIZE();

TIC_TAC_BOOL
clean_tic_tac_field(TIC_TAC_FIELD);

TIC_TAC_ERROR
fill_field_with_free_peace(TIC_TAC_FIELD);

TIC_TAC_ERROR
allocate_tic_tac_field(TIC_TAC_FIELD*);


TIC_TAC_WINNER
tic_tac_get_winner(TIC_TAC_FIELD);

TIC_TAC_ERROR 
init_tic_tac_field(TIC_TAC_FIELD*);

TIC_TAC_ERROR
set_piece(TIC_TAC_FIELD, size_t, size_t, TIC_TAC_PIECE);

TIC_TAC_BOOL 
can_move(TIC_TAC_FIELD, size_t , size_t);

#endif