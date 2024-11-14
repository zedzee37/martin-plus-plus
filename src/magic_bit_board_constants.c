#include "magic_bit_board.h"
#include <stdio.h>

MagicCell *rook_table[64] = { NULL };
MagicCell *bishop_table[64] = { NULL };
uint64_t rook_moves[8196] = { 0 };
uint64_t bishop_attacks[2048] = { 0 };
