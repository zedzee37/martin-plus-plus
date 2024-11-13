#ifndef BOARD_H
#define BOARD_H

#include "result.h"
#include <stdbool.h>
#include <stdint.h>

#define PIECE_COUNT 6

typedef enum PieceIndex {
	PAWN_IDX,
	KING_IDX,
	QUEEN_IDX,
	ROOK_IDX,
	BISHOP_IDX,
	KNIGHT_IDX,
} PieceIndex;

#define EMPTY_CHAR '.'

// Define the characters for each piece type
extern const char PIECE_CHARS[];

typedef struct Board {
	uint64_t pieces[PIECE_COUNT];
} Board;

extern bool board_is_piece_on(Board board, uint64_t pos);
extern bool board_is_piece_type_on(Board board, uint64_t pos, PieceIndex idx);
extern void board_print(Board board);
extern void board_set_default(Board *board);
extern uint64_t convert_pos(uint64_t x, uint64_t y);

#endif
