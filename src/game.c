#include "game.h"
#include <stdlib.h>

Game *game_alloc(Board *board) {
	Game *game = malloc(sizeof(Game));
	if (!game) {
		return NULL;
	}

	game->board = board;
	game->moves = malloc(sizeof(Move) * DEFAULT_MOVE_SIZE);
	game->is_whites_turn = true;

	return game;
}

void game_free(Game *game) {
	free(game->moves);
	free(game);
}
