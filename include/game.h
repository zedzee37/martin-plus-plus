#pragma once

#include "board.h"

#define DEFAULT_MOVE_SIZE 10

typedef struct Move {
} Move;

extern const char RANKS[];

typedef struct Game {
	Board *board;
	Move *moves;
	bool is_whites_turn;
} Game;

extern Game *game_alloc(Board *board);
extern void game_free(Game *game);
