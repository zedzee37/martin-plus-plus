#pragma once

#include "string.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint64_t BitBoard;

#define LEFT_EDGE 0x0101010101010101ULL
#define RIGHT_EDGE 0x8080808080808080ULL
#define TOP_EDGE 0xFF
#define BOTTOM_EDGE 0xFF00000000000000

#define IS_ON_RIGHT_EDGE(pos) ((pos) & RIGHT_EDGE)
#define IS_ON_LEFT_EDGE(pos) ((pos) & LEFT_EDGE)
#define IS_ON_TOP_EDGE(pos) ((pos) & TOP_EDGE)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & BOTTOM_EDGE)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))

extern void bit_board_print(BitBoard board);

typedef enum {
	W_PAWN,
	W_KING,
	W_QUEEN,
	W_KNIGHT,
	W_ROOK,
	W_BISHOP,
	B_PAWN,
	B_KING,
	B_QUEEN,
	B_KNIGHT,
	B_ROOK,
	B_BISHOP,
	PIECE_COUNT,
} PieceType;

#define HALF_PIECE_COUNT (PIECE_COUNT / 2)

inline bool piece_type_is_black(PieceType piece_type) {
	return piece_type >= HALF_PIECE_COUNT;
}
inline PieceType piece_type_reverse(PieceType piece_type) {
	return piece_type_is_black(piece_type)
			? piece_type - HALF_PIECE_COUNT
			: piece_type + HALF_PIECE_COUNT;
}
typedef struct {
	BitBoard pieces[PIECE_COUNT];
} Board;

extern Board *board_alloc(void);
extern void board_free(Board *board);
inline void board_reset(Board *board) {
	memset(board->pieces, 0, PIECE_COUNT * sizeof(BitBoard));
}
