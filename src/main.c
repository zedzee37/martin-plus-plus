#include "board.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
	Board board = board_init();
	uint64_t pos = 1ULL << 46;
	uint64_t piece = board_get_attack(board, pos, W_PAWN_IDX);
	print_board(piece | pos);
}
