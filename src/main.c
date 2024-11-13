#include "board.h"
#include <stdio.h>

int main() {
	Board board;
	board_set_default(&board);
	board_print(board);
	printf("\nwhite: %d, black: %d", board_get_white_material(board), board_get_black_material(board));
}
