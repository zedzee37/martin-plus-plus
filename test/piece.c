#include "board.h"
#include <assert.h>

int main(void) {
	PieceType type = W_PAWN;

	assert(!piece_type_is_black(type));
	assert(piece_type_reverse(B_QUEEN));
	assert(piece_type_reverse(type) == B_PAWN);
}
