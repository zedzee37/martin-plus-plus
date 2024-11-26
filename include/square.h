#pragma once

#include "board.h"
#include <stdint.h>

typedef uint32_t Square;

inline BitBoard get_pos(Square square) {
	return 1ULL << square;
}
