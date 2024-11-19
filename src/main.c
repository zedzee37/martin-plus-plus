#include "board.h"
#include <stdint.h>
#include <stdio.h>

int main() {
	Board board = board_init();
	board_print(board);
}
