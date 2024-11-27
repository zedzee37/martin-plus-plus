#include "board.h"
#include "moves.h"
#include "piece.h"
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
	PieceType piece_type = board_get_piece(board, position);
	bool is_black = piece_type_is_black(piece_type);
	BitBoard friendlies = board_get_friendlies(board, is_black);
	Piece piece = PIECES[piece_type];

	return piece_move(piece, board, position) & ~friendlies;
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
