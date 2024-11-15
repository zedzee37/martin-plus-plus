#include <stdbool.h>
#include <stdint.h>

#define IS_ON_RIGHT_EDGE(pos) ((pos) & 0x8080808080808080ULL)
#define IS_ON_LEFT_EDGE(pos) ((pos) & 0x0101010101010101ULL)
#define IS_ON_TOP_EDGE(pos) ((pos) & 0xFF)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & 0xFF00000000000000)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))

uint64_t generate_bishop_pattern(uint64_t pos) {
	uint64_t moves = 0;

	bool top_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool top_left = IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool bottom_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	bool bottom_left = IS_ON_LEFT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	for (int i = 1; i <= 6; i++) {
		if (!top_right && !(IS_ON_RIGHT_EDGE(pos >> (i * 7)) || IS_ON_TOP_EDGE(pos >> (i * 7)))) {
			moves |= pos >> (i * 7);
		} else {
			top_right = true;
		}

		if (!top_left && !(IS_ON_LEFT_EDGE(pos >> (i * 9)) || IS_ON_TOP_EDGE(pos >> (i * 9)))) {
			moves |= pos >> (i * 9);
		} else {
			top_left = true;
		}

		if (!bottom_right && !(IS_ON_RIGHT_EDGE(pos << (i * 9)) || IS_ON_BOTTOM_EDGE(pos << (i * 9)))) {
			moves |= pos << (i * 9);
		} else {
			bottom_right = true;
		}

		if (!bottom_left && !(IS_ON_LEFT_EDGE(pos << (i * 7)) || IS_ON_BOTTOM_EDGE(pos << (i * 7)))) {
			moves |= pos << (i * 7);
		} else {
			bottom_left = true;
		}
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
		if (!right_done && !IS_ON_RIGHT_EDGE(position << i)) {
			moves |= position << i;
		} else {
			right_done = true;
		}

		if (!left_done && !IS_ON_LEFT_EDGE(position >> i)) {
			moves |= position >> i;
		} else {
			left_done = true;
		}

		if (!down_done && !IS_ON_BOTTOM_EDGE(position << (i * 8))) {
			moves |= position << (i * 8);
		} else {
			down_done = true;
		}

		if (!up_done && !IS_ON_TOP_EDGE(position >> (i * 8))) {
			moves |= position >> (i * 8);
		} else {
			up_done = true;
		}
	}

	return moves;
}

int main() {
}