#include "board.h"
#include "magic_bit_board.h"
#include <stdbool.h>
#include <stdio.h>

MagicCell *rook_table[64] = { NULL };
MagicCell *bishop_table[64] = { NULL };
uint64_t rook_moves[8196] = { 0 };
uint64_t bishop_attacks[2048] = { 0 };

uint64_t generate_bishop_pattern(uint64_t pos) {
	uint64_t moves = 0;

	for (int i = 0; i <= 6; i++) {
	}

	return moves;
}

uint64_t generate_rook_pattern(uint64_t position) {
	uint64_t moves = 0ULL;

	bool right_done = false;
	bool left_done = false;
	bool up_done = false;
	bool down_done = false;
	for (int i = 1; i <= 6; i++) {
		// right
		if (!right_done && !is_on_edge(position << (i - 1))) {
			moves |= position << i;
		} else {
			right_done = true;
		}

		// left
		if (!left_done && !is_on_edge(position >> (i - 1))) {
			moves |= position >> i;
		} else {
			left_done = true;
		}

		// down
		if (!down_done && !is_on_edge(position << ((i - 1) * 8))) {
			moves |= position << (i * 8);
		} else {
			down_done = true;
		}

		// up
		if (!up_done && !is_on_edge(position >> ((i - 1) * 8))) {
			moves |= position >> (i * 8);
		} else {
			up_done = true;
		}
	}

	return moves;
}
