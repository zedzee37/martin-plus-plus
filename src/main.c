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
	uint64_t pos = 1ULL << 8;
	print_board(pos);
	uint64_t piece = get_piece_attack_pattern(pos, B_PAWN_IDX);
	print_board(piece);
}
