#include "board.h"
#include <stdio.h>

int main() {
	Board board;
	board_set_default(&board);
	board_print(board);
}
