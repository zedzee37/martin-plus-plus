#pragma once

#include "board.h"
#include <stdint.h>

typedef BitBoard (*PieceMoveCallback)(Board *board, Square square);
typedef BitBoard (*PieceAttackCallback)(Board *board, Square square);

typedef struct {
	uint32_t material;
	char debug_char;
	PieceMoveCallback move_callback;
	PieceAttackCallback attack_callback; // optional
} Piece;

extern const Piece PIECES[HALF_PIECE_COUNT];

extern BitBoard piece_move(Piece piece, Board *board, Square square);
extern BitBoard piece_attack(Piece piece, Board *board, Square square);

extern BitBoard pawn_move_callback(Board *board, Square square);
extern BitBoard king_move_callback(Board *board, Square square);
extern BitBoard queen_move_callback(Board *board, Square square);
extern BitBoard knight_move_callback(Board *board, Square square);
extern BitBoard rook_move_callback(Board *board, Square square);
extern BitBoard bishop_move_callback(Board *board, Square square);

extern BitBoard pawn_attack_callback(Board *board, Square square);
