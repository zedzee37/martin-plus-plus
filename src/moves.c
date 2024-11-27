#include "moves.h"
#include "board.h"

BitBoard cardinal_slider_move(Square square, BitBoard blockers, uint32_t extent) {
	BitBoard position = get_pos(square);
	BitBoard moves = 0ULL;

	blockers &= ~position;
	bool right_done = IS_ON_RIGHT_EDGE(position);
	bool left_done = IS_ON_LEFT_EDGE(position);
	bool up_done = IS_ON_TOP_EDGE(position);
	bool down_done = IS_ON_BOTTOM_EDGE(position);
	for (uint32_t i = 1; i <= extent; i++) {
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

BitBoard orthagonal_slider_move(Square square, BitBoard blockers, uint32_t extent) {
	BitBoard position = get_pos(square);
	BitBoard moves = 0;

	blockers &= ~position;
	bool top_right = IS_ON_RIGHT_EDGE(position) || IS_ON_TOP_EDGE(position);
	bool top_left = IS_ON_LEFT_EDGE(position) || IS_ON_TOP_EDGE(position);
	bool bottom_right = IS_ON_RIGHT_EDGE(position) || IS_ON_BOTTOM_EDGE(position);
	bool bottom_left = IS_ON_LEFT_EDGE(position) || IS_ON_BOTTOM_EDGE(position);
	for (uint32_t i = 1; i <= extent; i++) {
		int p = i - 1;

		if (!top_right && !(IS_ON_RIGHT_EDGE(position >> (p * 7)) || IS_ON_TOP_EDGE(position >> (p * 7))) && !((position >> (p * 7)) & blockers)) {
			moves |= position >> (i * 7);
		} else {
			top_right = true;
		}

		if (!top_left && !(IS_ON_LEFT_EDGE(position >> (p * 9)) || IS_ON_TOP_EDGE(position >> (p * 9))) && !((position >> (p * 9)) & blockers)) {
			moves |= position >> (i * 9);
		} else {
			top_left = true;
		}

		if (!bottom_right && !(IS_ON_RIGHT_EDGE(position << (p * 9)) || IS_ON_BOTTOM_EDGE(position << (p * 9))) && !((position << (p * 9)) & blockers)) {
			moves |= position << (i * 9);
		} else {
			bottom_right = true;
		}

		if (!bottom_left && !(IS_ON_LEFT_EDGE(position << (p * 7)) || IS_ON_BOTTOM_EDGE(position << (p * 7))) && !((position << (p * 7)) & blockers)) {
			moves |= position << (i * 7);
		} else {
			bottom_left = true;
		}
	}

	return moves;
}

BitBoard knight_move(Square square) {
	BitBoard position = get_pos(square);
	BitBoard attack = 0;

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

BitBoard pawn_move(Square square, bool is_black, BitBoard blockers, BitBoard enemy_pawns, BitBoard *en_passant_pos) {
	BitBoard position = get_pos(square);
	BitBoard attack = 0;
	bool can_move_right = !IS_ON_RIGHT_EDGE(position);
	bool can_move_left = !IS_ON_LEFT_EDGE(position);
	bool can_move_forward = false;
	BitBoard forward_pos = position;

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
		BitBoard pos = forward_pos << 1;
		*en_passant_pos = pos;
		attack |= pos;
	}

	if (can_move_left && (position >> 1) & enemy_pawns && can_move_forward && !((forward_pos >> 1) & enemy_pawns)) {
		BitBoard pos = forward_pos >> 1;
		*en_passant_pos = pos;
		attack |= pos;
	}

	return attack;
}
