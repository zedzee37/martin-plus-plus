#include "board.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
	Board board = board_init();
	uint64_t pos = 1ULL << 42;
	uint64_t piece = board_get_attack(board, pos, W_KNIGHT_IDX);
	print_board(board_get_attacked(board, piece, W_KNIGHT_IDX));
}
