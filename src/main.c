#include "board.h"
#include <stdint.h>
#include <stdio.h>

int main() {
	Board board;
	board_set_default(&board);
	board_print(board);
	printf("\nwhite: %d, black: %d\n", board_get_white_material(board), board_get_black_material(board));

	for (int j = 0; j < 64; j++) {
		uint64_t rook_pattern = generate_rook_pattern(1ULL << j);
		for (int i = 0; i < 64; i++) {
			uint64_t pos = 1ULL << i;

			if (pos & rook_pattern) {
				printf(" x ");
			} else {
				printf(" . ");
			}

			if (!((i + 1) % 8)) {
				printf("\n");
			}
		}
		printf("\n");
	}

	uint64_t bishop_pattern = generate_bishop_pattern(0);
	for (int i = 0; i < 64; i++) {
		uint64_t pos = 1ULL << i;

		if (pos & bishop_pattern) {
			printf(" x ");
		} else {
			printf(" . ");
		}

		if (!((i + 1) % 8)) {
			printf("\n");
		}
	}
	printf("\n");
}
