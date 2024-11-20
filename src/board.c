#include "board.h"
#include "attacks.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

const PieceInfo PIECE_INFO[] = {
	[W_PAWN_IDX] = { 'P', 1 },
	[W_KING_IDX] = { 'K', 0 },
	[W_QUEEN_IDX] = { 'Q', 9 },
	[W_ROOK_IDX] = { 'R', 5 },
	[W_BISHOP_IDX] = { 'B', 3 },
	[W_KNIGHT_IDX] = { 'N', 3 }
};

Board board_init() {
	Board board;
	board_set_default(&board);
	return board;
}

void board_set_default(Board *board) {
	board_reset(board);

	// Set up white pawns
	board->pieces[W_PAWN_IDX] |= 0x000000000000FF00ULL;
	// Set up black pawns
	board->pieces[B_PAWN_IDX] |= 0x00FF000000000000ULL;

	// Set up kings
	board->pieces[W_KING_IDX] |= 0x0000000000000010ULL; // White king at E1
	board->pieces[B_KING_IDX] |= 0x0800000000000000ULL; // Black king at E8

	// Set up queens
	board->pieces[W_QUEEN_IDX] |= 0x0000000000000008ULL; // White queen at D1
	board->pieces[B_QUEEN_IDX] |= 0x1000000000000000ULL; // Black queen at D8

	// Set up rooks
	board->pieces[W_ROOK_IDX] |= 0x0000000000000081ULL; // White rooks at A1 and H1
	board->pieces[B_ROOK_IDX] |= 0x8100000000000000ULL; // Black rooks at A8 and H8

	// Set up bishops
	board->pieces[W_BISHOP_IDX] |= 0x0000000000000024ULL; // White bishops at C1 and F1
	board->pieces[B_BISHOP_IDX] |= 0x2400000000000000ULL; // Black bishops at C8 and F8

	// Set up knights
	board->pieces[W_KNIGHT_IDX] |= 0x0000000000000042ULL; // White knights at B1 and G1
	board->pieces[B_KNIGHT_IDX] |= 0x4200000000000000ULL; // Black knights at B8 and G8
}

void board_reset(Board *board) {
	for (PieceIndex i = 0; i < PIECE_COUNT; i++) {
		board->pieces[i] = 0;
	}
}

bool board_is_piece_on(Board board, uint64_t pos) {
	for (int i = 0; i < PIECE_COUNT; i++) {
		if (board.pieces[i] & pos) {
			return true;
		}
	}
	return false;
}

bool board_is_piece_type_on(Board board, uint64_t pos, PieceIndex idx) {
	return board.pieces[idx] & pos;
}

uint32_t board_get_white_material(Board board) {
	return get_material(board.pieces);
}

uint32_t board_get_black_material(Board board) {
	return get_material(board.pieces + PIECE_COUNT / 2);
}

void board_print(Board board) {
	for (uint64_t i = 0; i < 64; i++) {
		uint64_t pos = 1ULL << i;

		bool found_piece = false;
		for (PieceIndex piece_idx = 0; piece_idx < PIECE_COUNT; piece_idx++) {
			if (board_is_piece_type_on(board, pos, piece_idx)) {
				found_piece = true;

				char ch = get_piece_info(piece_idx).debug_char;

				printf(" %c ", ch);
				break;
			}
		}

		if (!found_piece) {
			printf(" %c ", EMPTY_CHAR);
		}

		if (!((i + 1) % 8)) {
			printf("\n");
		}
	}
}

uint32_t get_material(uint64_t pieces[PIECE_COUNT / 2]) {
	uint32_t material = 0;

	for (uint64_t i = 0; i < 64; i++) {
		uint64_t pos = 1ULL << i;

		for (PieceIndex idx = 0; idx < PIECE_COUNT / 2; idx++) {
			if (pieces[idx] & pos) {
				material += get_piece_info(idx).material;
			}
		}
	}

	return material;
}

PieceInfo get_piece_info(PieceIndex idx) {
	return PIECE_INFO[clamp_piece_idx(idx)];
}

uint32_t clamp_piece_idx(PieceIndex piece_idx) {
	if (piece_idx >= PIECE_COUNT / 2) {
		return piece_idx - PIECE_COUNT / 2;
	}
	return piece_idx;
}

uint64_t get_piece_attack_pattern(uint64_t pos, PieceIndex piece_type) {
	uint64_t attack = 0;

	switch (clamp_piece_idx(piece_type)) {
		case W_PAWN_IDX:
			break;
		case W_KING_IDX:
			break;
		case W_QUEEN_IDX:
			attack = orthagonal_slider_attack(pos, 0) | cardinal_slider_attack(pos, 0);
			break;
		case W_BISHOP_IDX:
			attack = orthagonal_slider_attack(pos, 0);
			break;
		case W_ROOK_IDX:
			attack = cardinal_slider_attack(pos, 0);
			break;
		case W_KNIGHT_IDX:
			break;
	}

	return attack;
}
