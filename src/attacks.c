#include "attacks.h"
#include "helpers.h"
#include <stdbool.h>

uint64_t cardinal_slider_attack(uint64_t position, uint64_t blockers) {
	uint64_t moves = 0ULL;

	bool right_done = IS_ON_RIGHT_EDGE(position);
	bool left_done = IS_ON_LEFT_EDGE(position);
	bool up_done = IS_ON_TOP_EDGE(position);
	bool down_done = IS_ON_BOTTOM_EDGE(position);
	for (int i = 1; i <= 7; i++) {
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

uint64_t orthagonal_slider_attack(uint64_t pos, uint64_t blockers) {
	uint64_t moves = 0;

	bool top_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool top_left = IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool bottom_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	bool bottom_left = IS_ON_LEFT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	for (int i = 1; i <= 6; i++) {
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
