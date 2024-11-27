#pragma once

#include "board.h"
#include "square.h"

extern BitBoard cardinal_slider_move(Square position, BitBoard blockers, uint32_t extent);
extern BitBoard orthagonal_slider_move(Square position, BitBoard blockers, uint32_t extent);
extern BitBoard knight_move(Square position);
extern BitBoard pawn_move(Square position, bool is_black, BitBoard blockers, BitBoard enemy_pawns, BitBoard *en_passant_pos);
