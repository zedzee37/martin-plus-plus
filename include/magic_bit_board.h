#ifndef MAGIC_BIT_BOARD
#define MAGIC_BIT_BOARD

#include <stdint.h>

// Simple container for the mask and magic number
typedef struct MagicCell {
	uint64_t blocker_mask;
	uint64_t magic_number;
} MagicCell;

extern MagicCell *rook_table[64];
extern MagicCell *bishop_table[64];
extern uint64_t rook_attacks[8196];
extern uint64_t bishop_attacks[2048];

extern uint64_t get_rook_attacks(uint64_t pos, uint64_t blockers);
extern uint64_t get_bishop_attacks(uint64_t pos, uint64_t blockers);
extern uint64_t get_magic_index(MagicCell cell, uint64_t blockers);

#endif
