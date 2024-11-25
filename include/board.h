#pragma once

#include "helpers.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct PieceInfo {
	char debug_char;
	uint32_t material;
} PieceInfo;

extern const PieceInfo PIECE_INFO[];

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
extern uint64_t board_get_friendly(Board board, bool is_black);
extern uint64_t board_get_enemy(Board board, bool is_black);
extern uint64_t board_get_attack(Board board, uint64_t pos, PieceIndex piece_type);
extern uint64_t board_get_attacked(Board board, uint64_t moves, PieceIndex piece);

extern uint32_t get_material(uint64_t pieces[PIECE_COUNT / 2]);
extern PieceInfo get_piece_info(PieceIndex idx);
extern uint32_t clamp_piece_idx(PieceIndex piece_idx);
extern uint64_t glob_pieces(uint64_t *pieces, uint32_t count);
