#include "board.h"
#include "square.h"
#include <stdio.h>
#include <stdlib.h>

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

Board *board_alloc(void) {
	Board *board = malloc(sizeof(Board));
	if (!board) {
		return NULL;
	}

	board_reset(board);

	return board;
}

void board_free(Board *board) {
	free(board);
}
