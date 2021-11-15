#ifndef TIC_TAC_TYPES_H
#define TIC_TAC_TYPES_H

#include <stdint.h>
#include <stddef.h>

/*! typedef */
typedef uint8_t TIC_TAC_BOOL;
typedef uint8_t TIC_TAC_ERROR;
typedef uint8_t TIC_TAC_PIECE;
typedef uint8_t TIC_TAC_PLAYER;
typedef uint8_t TIC_TAC_WINNER;

/*! TIC_TAC_BOOL */
#define TIC_TAC_BOOL_FALSE 				0x00
#define TIC_TAC_BOOL_TRUE 				0x01

/*! TIC_TAC_ERROR */
#define TIC_TAC_ERROR_NO_PROBLEM 		0x00
#define TIC_TAC_ERROR_NOT_EMPTY_PIECE 	0x01
#define TIC_TAC_ERROR_MEMORRY_PROBLEM 	0xff

/*! TIC_TAC_PIECE */
#define TIC_TAC_PIECE_FREE_PLACE		0x00
#define TIC_TAC_PIECE_TIC				0x01
#define TIC_TAC_PIECE_TAC				0x02

/*! TIC_TAC_PLAYER */
#define TIC_TAC_PLAYER_NO				0x01
#define TIC_TAC_PLAYER_TIC				0x01
#define TIC_TAC_PLAYER_TAC				0x02

/*! TIC_TAC_WINNER */
#define TIC_TAC_WINNER_NO_WINNER		0x00
#define TIC_TAC_WINNER_TIC_WIN			0x01
#define TIC_TAC_WINNER_TAC_WIN			0x02
#define TIC_TAC_WINNER_FRIENDS_WIN		0x03

#endif