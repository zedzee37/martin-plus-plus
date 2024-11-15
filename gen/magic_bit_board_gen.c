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

MagicCell rook_magics[64];
MagicCell bishop_magics[64];

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

uint64_t magic_index(MagicCell magic_cell, uint64_t blockers) {
	blockers &= magic_cell.blocker_mask;

	// Calculate the index using the magic number and bit shift
	uint64_t shift = 64 - __builtin_popcountll(magic_cell.blocker_mask);
	return (blockers * magic_cell.magic_number) >> shift;
}

bool is_magic_valid_rook(uint64_t magic, uint64_t pos, uint64_t mask) {
	int blocker_count;
	uint64_t *blockers = generate_blocker_configs(mask, &blocker_count);

	// Array to hold computed attack bitboards for validation
	uint64_t *used_attacks = calloc(blocker_count, sizeof(uint64_t));
	if (!used_attacks) {
		free(blockers);
		exit(EXIT_FAILURE);
	}

	uint64_t shift = 64 - __builtin_popcountll(mask); // Calculate the shift for magic indexing
	for (int i = 0; i < blocker_count; i++) {
		uint64_t blockers_config = blockers[i];
		// if (blockers_config == 0) {
		// 	continue;
		// }
		uint64_t attack = generate_rook_pattern(pos, blockers_config); // Change to `generate_bishop_pattern` for bishops
		uint64_t index = (blockers_config * magic) >> shift;

		if (used_attacks[index] == 0) {
			used_attacks[index] = attack;
		} else if (used_attacks[index] != attack) {
			// Conflict found
			free(blockers);
			free(used_attacks);
			return false;
		}
	}

	free(blockers);
	free(used_attacks);
	return true;
}

bool is_magic_valid_bishop(uint64_t magic, uint64_t pos, uint64_t mask) {
	int blocker_count;
	uint64_t *blockers = generate_blocker_configs(mask, &blocker_count);

	// Array to hold computed attack bitboards for validation
	uint64_t *used_attacks = calloc(blocker_count, sizeof(uint64_t));
	if (!used_attacks) {
		free(blockers);
		exit(EXIT_FAILURE);
	}

	uint64_t shift = 64 - __builtin_popcountll(mask); // Calculate the shift for magic indexing
	for (int i = 0; i < blocker_count; i++) {
		uint64_t blockers_config = blockers[i];
		uint64_t attack = generate_rook_pattern(pos, blockers_config); // Change to `generate_bishop_pattern` for bishops
		uint64_t index = (blockers_config * magic) >> shift;

		if (used_attacks[index] == 0) {
			used_attacks[index] = attack;
		} else if (used_attacks[index] != attack) {
			// Conflict found
			free(blockers);
			free(used_attacks);
			return false;
		}
	}

	free(blockers);
	free(used_attacks);
	return true;
}

MagicCell find_rook_magic(uint64_t pos) {
	MagicCell result;
	result.blocker_mask = generate_rook_pattern(pos, 0);

	if (result.blocker_mask == 0) {
		result.magic_number = 0;
		return result;
	}

	// Attempt to find a valid magic number
	while (true) {
		uint64_t magic = rand64() & rand64() & rand64(); // Generate a random 64-bit magic number
		if (is_magic_valid_rook(magic, pos, result.blocker_mask)) {
			result.magic_number = magic;
			return result;
		}
	}
}

MagicCell find_bishop_magic(uint64_t pos) {
	MagicCell result;
	result.blocker_mask = generate_bishop_pattern(pos, 0);

	// Attempt to find a valid magic number
	while (true) {
		uint64_t magic = rand64() & rand64() & rand64(); // Generate a random 64-bit magic number
		if (is_magic_valid_bishop(magic, pos, result.blocker_mask)) {
			result.magic_number = magic;
			return result;
		}
	}
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

void generate_rook_magics() {
	for (int i = 0; i < 64; i++) {
		uint64_t pos = 1ULL << i;
		rook_magics[i] = find_rook_magic(pos);
		printf("Found magic for: %d\n", i);
	}
}

void generate_bishop_magics() {
	for (int i = 0; i < 64; i++) {
		uint64_t pos = 1ULL << i;
		bishop_magics[i] = find_bishop_magic(pos);
	}
}

int main() {
	generate_rook_magics();
	return 0;
}
