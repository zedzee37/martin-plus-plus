#include "attacks.h"
#include "helpers.h"
#include <stdbool.h>
#include <stdio.h>

uint64_t cardinal_slider_attack(uint64_t position, uint64_t blockers, uint32_t extent) {
	uint64_t moves = 0ULL;

	blockers &= ~position;
	bool right_done = IS_ON_RIGHT_EDGE(position);
	bool left_done = IS_ON_LEFT_EDGE(position);
	bool up_done = IS_ON_TOP_EDGE(position);
	bool down_done = IS_ON_BOTTOM_EDGE(position);
	for (int i = 1; i <= extent; i++) {
		int p = i - 1;

		if (!right_done && !IS_ON_RIGHT_EDGE(position << p) && !((position << p) & blockers)) {
			moves |= position << i;
		} else {
			right_done = true;
		}

		if (!left_done && !IS_ON_LEFT_EDGE(position >> p) && !((position >> p) & blockers)) {
			moves |= position >> i;
		} else {
			left_done = true;
		}

		if (!down_done && !IS_ON_BOTTOM_EDGE(position << (p * 8)) && !((position << (p * 8)) & blockers)) {
			moves |= position << (i * 8);
		} else {
			down_done = true;
		}

		if (!up_done && !IS_ON_TOP_EDGE(position >> (p * 8)) && !((position >> (p * 8)) & blockers)) {
			moves |= position >> (i * 8);
		} else {
			up_done = true;
		}
	}

	return moves;
}

uint64_t orthagonal_slider_attack(uint64_t pos, uint64_t blockers, uint32_t extent) {
	uint64_t moves = 0;

	blockers &= ~pos;
	bool top_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool top_left = IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool bottom_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	bool bottom_left = IS_ON_LEFT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	for (int i = 1; i <= extent; i++) {
		int p = i - 1;

		if (!top_right && !(IS_ON_RIGHT_EDGE(pos >> (p * 7)) || IS_ON_TOP_EDGE(pos >> (p * 7))) && !((pos >> (p * 7)) & blockers)) {
			moves |= pos >> (i * 7);
		} else {
			top_right = true;
		}

		if (!top_left && !(IS_ON_LEFT_EDGE(pos >> (p * 9)) || IS_ON_TOP_EDGE(pos >> (p * 9))) && !((pos >> (p * 9)) & blockers)) {
			moves |= pos >> (i * 9);
		} else {
			top_left = true;
		}

		if (!bottom_right && !(IS_ON_RIGHT_EDGE(pos << (p * 9)) || IS_ON_BOTTOM_EDGE(pos << (p * 9))) && !((pos << (p * 9)) & blockers)) {
			moves |= pos << (i * 9);
		} else {
			bottom_right = true;
		}

		if (!bottom_left && !(IS_ON_LEFT_EDGE(pos << (p * 7)) || IS_ON_BOTTOM_EDGE(pos << (p * 7))) && !((pos << (p * 7)) & blockers)) {
			moves |= pos << (i * 7);
		} else {
			bottom_left = true;
		}
	}

	return moves;
}

// for the top - 2
/*

0000000000000000000000000000000000000000000000001111111111111111
000000000000FFFF


// for the right + 2
/*

0000001100000011000000110000001100000011000000110000001100000011
303030303030303

*/

// for the left - 2
/*

1100000011000000110000001100000011000000110000001100000011000000
C0C0C0C0C0C0C0C0

*/

// for the bottom + 2
/*

1111111111111111000000000000000000000000000000000000000000000000
FFFF000000000000

*/
uint64_t knight_attack(uint64_t position) {
	uint64_t attack = 0;

	if (!IS_ON_LEFT_EDGE(position)) {
		if (!(position & 0xFFFF000000000000)) { // bottom
			attack |= position << 15;
		}

		if (!(position & 0x000000000000FFFF)) { // top
			attack |= position >> 17;
		}
	}

	if (!IS_ON_RIGHT_EDGE(position)) {
		if (!(position & 0xFFFF000000000000)) { // bottom
			attack |= position << 17;
		}

		if (!(position & 0x000000000000FFFF)) { // top
			attack |= position >> 15;
		}
	}

	if (!IS_ON_TOP_EDGE(position)) {
		if (!(position & 0xC0C0C0C0C0C0C0C0)) { // right
			attack |= position >> 6;
		}

		if (!(position & 0x303030303030303)) { // left
			attack |= position >> 10;
		}
	}

	if (!IS_ON_BOTTOM_EDGE(position)) {
		if (!(position & 0xC0C0C0C0C0C0C0C0)) { // right
			attack |= position << 10;
		}

		if (!(position & 0x303030303030303)) { // left
			attack |= position << 6;
		}
	}

	return attack;
}

uint64_t pawn_attack(uint64_t position, bool is_black, uint64_t blockers, uint64_t enemy_pawns, uint64_t *en_passant_pos) {
	uint64_t attack = 0;
	bool can_move_right = !IS_ON_RIGHT_EDGE(position);
	bool can_move_left = !IS_ON_LEFT_EDGE(position);
	bool can_move_forward = false;
	uint64_t forward_pos = position;

	if (is_black) {
		can_move_forward = !IS_ON_TOP_EDGE(position);

		if (can_move_forward) {
			forward_pos >>= 8;
		}
	} else {
		can_move_forward = !IS_ON_BOTTOM_EDGE(position);

		if (can_move_forward) {
			forward_pos <<= 8;
		}
	}

	if (can_move_forward) {
		if (can_move_right && (forward_pos << 1) & blockers) {
			attack |= forward_pos << 1;
		}

		if (can_move_left && (forward_pos >> 1) & blockers) {
			attack |= forward_pos >> 1;
		}

		if (!(forward_pos & blockers)) {
			attack |= forward_pos;
		}
	}

	// for en passant
	if (can_move_right && (position << 1) & enemy_pawns && can_move_forward && !((forward_pos << 1) & enemy_pawns)) {
		uint64_t pos = forward_pos << 1;
		*en_passant_pos = pos;
		attack |= pos;
	}

	if (can_move_left && (position >> 1) & enemy_pawns && can_move_forward && !((forward_pos >> 1) & enemy_pawns)) {
		uint64_t pos = forward_pos >> 1;
		*en_passant_pos = pos;
		attack |= pos;
	}

	return attack;
}
