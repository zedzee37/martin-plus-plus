#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_ON_RIGHT_EDGE(pos) ((pos) & 0x8080808080808080ULL)
#define IS_ON_LEFT_EDGE(pos) ((pos) & 0x0101010101010101ULL)
#define IS_ON_TOP_EDGE(pos) ((pos) & 0xFF)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & 0xFF00000000000000)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))

uint64_t *rook_moves[8196] = { NULL };
uint64_t *bishop_attacks[2048] = { NULL };

typedef struct MagicCell {
	uint64_t blocker_mask;
	uint64_t magic_number;
} MagicCell;

uint64_t generate_bishop_pattern(uint64_t pos, uint64_t blockers) {
	uint64_t moves = 0;

	bool top_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool top_left = IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos);
	bool bottom_right = IS_ON_RIGHT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	bool bottom_left = IS_ON_LEFT_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos);
	for (int i = 1; i <= 6; i++) {
		if (!top_right && !(IS_ON_RIGHT_EDGE(pos >> (i * 7)) || IS_ON_TOP_EDGE(pos >> (i * 7))) && !((pos >> (i * 7)) & blockers)) {
			moves |= pos >> (i * 7);
		} else {
			top_right = true;
		}

		if (!top_left && !(IS_ON_LEFT_EDGE(pos >> (i * 9)) || IS_ON_TOP_EDGE(pos >> (i * 9))) && !((pos >> (i * 9)) & blockers)) {
			moves |= pos >> (i * 9);
		} else {
			top_left = true;
		}

		if (!bottom_right && !(IS_ON_RIGHT_EDGE(pos << (i * 9)) || IS_ON_BOTTOM_EDGE(pos << (i * 9))) && !((pos << (i * 9)) & blockers)) {
			moves |= pos << (i * 9);
		} else {
			bottom_right = true;
		}

		if (!bottom_left && !(IS_ON_LEFT_EDGE(pos << (i * 7)) || IS_ON_BOTTOM_EDGE(pos << (i * 7))) && !((pos << (i * 7)) & blockers)) {
			moves |= pos << (i * 7);
		} else {
			bottom_left = true;
		}
	}

	return moves;
}

uint64_t generate_rook_pattern(uint64_t position, uint64_t blockers) {
	uint64_t moves = 0ULL;

	bool right_done = false;
	bool left_done = false;
	bool up_done = false;
	bool down_done = false;
	for (int i = 1; i <= 6; i++) {
		if (!right_done && !IS_ON_RIGHT_EDGE(position << i) && !((position << i) & blockers)) {
			moves |= position << i;
		} else {
			right_done = true;
		}

		if (!left_done && !IS_ON_LEFT_EDGE(position >> i) && !((position >> i) & blockers)) {
			moves |= position >> i;
		} else {
			left_done = true;
		}

		if (!down_done && !IS_ON_BOTTOM_EDGE(position << (i * 8)) && !((position << (i * 8)) & blockers)) {
			moves |= position << (i * 8);
		} else {
			down_done = true;
		}

		if (!up_done && !IS_ON_TOP_EDGE(position >> (i * 8)) && !((position >> (i * 8)) & blockers)) {
			moves |= position >> (i * 8);
		} else {
			up_done = true;
		}
	}

	return moves;
}

uint64_t *generate_blocker_configs(uint64_t mask, int *count) {
	// Count the number of set bits in the mask (relevant squares)
	int num_bits = __builtin_popcountll(mask);
	int num_configs = 1 << num_bits; // Total configurations = 2^num_bits

	// Allocate memory to store all configurations
	uint64_t *configs = malloc(num_configs * sizeof(uint64_t));
	if (!configs) {
		exit(EXIT_FAILURE);
	}

	// List all permutations of blockers
	for (int i = 0; i < num_configs; i++) {
		uint64_t blockers = 0;
		uint64_t temp_mask = mask;
		for (int j = 0; j < num_bits; j++) {
			// Extract the next relevant square
			int bit_index = __builtin_ctzll(temp_mask); // Find the index of the least significant set bit
			temp_mask &= temp_mask - 1; // Remove the least significant set bit

			// Set the bit in the blockers bitboard if the j-th bit in `i` is set
			if (i & (1 << j)) {
				blockers |= (1ULL << bit_index);
			}
		}
		configs[i] = blockers;
	}

	*count = num_configs; // Store the number of configurations
	return configs;
}

uint64_t rand64() {
	uint32_t left = rand();
	uint32_t right = rand();
	return ((uint64_t)left << 32) | right;
}

bool is_magic_valid(uint64_t magic, uint64_t pos, uint64_t mask) {
}

MagicCell find_magic(uint64_t pos, uint64_t mask) {
	while (true) {
		uint64_t magic = rand64() & rand64() & rand64();
	}
}

MagicCell find_rook_magic(uint64_t pos) {
	return find_magic(pos, generate_rook_pattern(pos, 0));
}

MagicCell find_bishop_magic(uint64_t pos) {
	return find_magic(pos, generate_bishop_pattern(pos, 0));
}

void print_board(uint64_t board) {
	for (int i = 0; i < 64; i++) {
		uint64_t p = 1ULL << i;

		if (p & board) {
			printf(" x ");
		} else {
			printf(" . ");
		}

		if ((i + 1) % 8 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

int main() {
	uint64_t pos = 1ULL << 43;

	uint64_t mask = generate_rook_pattern(pos, 0);
	int amt;
	uint64_t *configs = generate_blocker_configs(mask, &amt);

	for (int j = 0; j < amt; j++) {
		print_board(configs[j]);
	}

	free(configs);
}
