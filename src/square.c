#include "square.h"

uint8_t get_square_idx(uint64_t pos) {
	for (int i = 0; i < 64; i++) {
		uint64_t current_pos = get_square_pos(i);

		if (current_pos == pos) {
			return i;
		}
	}

	return 0;
}

uint64_t get_square_pos(uint8_t shift) {
	return 1ULL << shift;
}
