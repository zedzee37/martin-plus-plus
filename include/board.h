#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>

#define PIECE_COUNT 12

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

extern bool board_is_piece_on(Board board, uint64_t pos);
extern bool board_is_piece_type_on(Board board, uint64_t pos, PieceIndex idx);
extern uint64_t board_get_attackers(Board board, uint64_t pos);
extern uint32_t board_get_white_material(Board board);
extern uint32_t board_get_black_material(Board board);
extern bool board_is_white_checkmated(Board board);
extern bool board_is_black_checkmated(Board board);
extern void board_print(Board board);
extern void board_set_default(Board *board);

extern uint64_t convert_pos(uint64_t x, uint64_t y);
extern uint32_t get_material(uint64_t pieces[PIECE_COUNT / 2]);
extern uint64_t generate_bishop_pattern(uint64_t pos);
extern uint64_t generate_rook_pattern(uint64_t pos);
extern uint64_t generate_knight_pattern(uint64_t pos);
extern uint64_t generate_pawn_pattern(uint64_t pos);
extern uint64_t generate_king_pattern(uint64_t pos);

#endif
