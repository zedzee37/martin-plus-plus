#include "board.h"
#include "moves.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bit_board_print(BitBoard board) {
	for (Square square = 0; square < 64; square++) {
		uint64_t pos = get_pos(square);

		if (pos & board) {
			printf(" x ");
		} else {
			printf(" . ");
		}

		if ((square + 1) % 8 == 0) {
			printf("\n");
		}
	}
}

Board *board_alloc(void) {
	Board *board = malloc(sizeof(Board));
	if (!board) {
		return NULL;
	}

	board_reset(board);

	return board;
}

void board_free(Board *board) {
	free(board);
}

PieceType board_get_piece(Board *board, Square position) {
	BitBoard pos = get_pos(position);
	for (PieceType i = 0; i < PIECE_COUNT; i++) {
		if (board->pieces[i] & pos) {
			return i;
		}
	}
	return NONE;
}

BitBoard board_get_moves(Board *board, Square position) {
	PieceType piece = board_get_piece(board, position);
	BitBoard moves = 0;
	bool is_black = piece_type_is_black(piece);
	BitBoard friendlies = board_get_friendlies(board, is_black);
	BitBoard enemies = board_get_enemies(board, is_black);
	BitBoard blockers = friendlies | enemies;
	BitBoard en_passant_move = 0;
	BitBoard enemy_pawns = 0;

	switch (piece_type_clamp(piece)) {
		case W_PAWN:
			enemy_pawns = board->pieces[W_PAWN * (is_black * HALF_PIECE_COUNT)];
			moves = pawn_move(position, is_black, blockers, enemy_pawns, &en_passant_move);
			break;
		case W_KING:
			moves = cardinal_slider_move(position, blockers, 1) | orthagonal_slider_move(position, blockers, 1);
			break;
		case W_QUEEN:
			moves = cardinal_slider_move(position, blockers, 7) | orthagonal_slider_move(position, blockers, 7);
			break;
		case W_KNIGHT:
			moves = knight_move(position);
			break;
		case W_BISHOP:
			moves = orthagonal_slider_move(position, blockers, 7);
			break;
		case W_ROOK:
			moves = cardinal_slider_move(position, blockers, 7);
			break;
		default:
			break;
	}

	return moves;
}

BitBoard board_get_friendlies(Board *board, bool is_black) {
	BitBoard *pieces = board->pieces;
	if (is_black) {
		pieces += 6;
	}

	return glob_pieces(pieces);
}

BitBoard board_get_enemies(Board *board, bool is_black) {
	BitBoard *pieces = board->pieces;
	if (!is_black) {
		pieces += 6;
	}

	return glob_pieces(pieces);
}

BitBoard glob_pieces(BitBoard pieces[HALF_PIECE_COUNT]) {
	BitBoard globbed = 0;

	for (PieceType i = 0; i < HALF_PIECE_COUNT; i++) {
		globbed |= pieces[i];
	}

	return globbed;
}
