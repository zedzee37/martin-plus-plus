#include "assert.h"
#include "board.h"
#include <stdio.h>

int main() {
	Board board = board_init();
	assert(board_get_square_attackers(board, 0) == 0);

	board_reset(&board);

	board.pieces[W_QUEEN_IDX] = 0x8000000;
	board.pieces[B_PAWN_IDX] = 0x1000000000;

	assert(board_get_square_attackers(board, 0x1000000000));

	return 0;
}
