#include "board.h"
#include "square.h"
#include <stdio.h>

void bit_board_print(BitBoard board) {
	for (Square square = 0; square < 64; square++) {
		uint64_t pos = get_pos(square);

		if (pos & board) {
			printf(" x ");
		} else {
			printf(" . ");
		}

		if ((square + 1) % 8 == 0) {
			printf("\n");
		}
	}
}
