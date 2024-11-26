#include "board.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
	Board board = board_init();
	uint64_t pos = 1ULL << 42;
	uint64_t piece = board_get_moves(board, pos, W_KNIGHT_IDX);
}
