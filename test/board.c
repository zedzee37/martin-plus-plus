#include "board.h"
#include <assert.h>
#include <stdint.h>
#include <string.h> // For memcmp

int main(void) {
	Board *board = board_alloc();

	uint64_t correct[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	assert(memcmp(board->pieces, correct, PIECE_COUNT * sizeof(BitBoard)) == 0);

	board_free(board);
	return 0;
}
