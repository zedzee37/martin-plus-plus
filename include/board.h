#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>

#define PIECE_COUNT 12

#define IS_ON_RIGHT_EDGE(pos) ((pos) & 0x8080808080808080ULL)
#define IS_ON_LEFT_EDGE(pos) ((pos) & 0x0101010101010101ULL)
#define IS_ON_TOP_EDGE(pos) ((pos) & 0xFF)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & 0xFF00000000000000)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))

typedef enum PieceIndex {
	W_PAWN_IDX,
	W_KING_IDX,
	W_QUEEN_IDX,
	W_ROOK_IDX,
	W_BISHOP_IDX,
	W_KNIGHT_IDX,
	B_PAWN_IDX,
	B_KING_IDX,
	B_QUEEN_IDX,
	B_ROOK_IDX,
	B_BISHOP_IDX,
	B_KNIGHT_IDX,
} PieceIndex;

#define EMPTY_CHAR '.'

// Define the characters for each piece type
extern const char PIECE_CHARS[];
extern const uint32_t PIECE_MATERIAL[];

typedef struct Board {
	uint64_t pieces[PIECE_COUNT];
} Board;

extern Board board_init();
extern void board_reset(Board *board);
extern void board_set_default(Board *board);
extern bool board_is_piece_on(Board board, uint64_t pos);
extern bool board_is_piece_type_on(Board board, uint64_t pos, PieceIndex idx);
extern bool board_is_white_checkmated(Board board);
extern bool board_is_black_checkmated(Board board);
extern void board_print(Board board);

extern uint32_t get_material(uint64_t pieces[PIECE_COUNT / 2]);

#endif
