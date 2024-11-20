#include "board.h"
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
	board_print(board);
	uint64_t queen = get_piece_attack_pattern(1ULL << 2, W_KNIGHT_IDX);
	print_board(queen);
}
