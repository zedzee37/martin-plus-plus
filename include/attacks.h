#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdbool.h>
#include <stdint.h>

extern uint64_t cardinal_slider_attack(uint64_t position, uint64_t blockers, uint32_t extent);
extern uint64_t orthagonal_slider_attack(uint64_t position, uint64_t blockers, uint32_t extent);
extern uint64_t knight_attack(uint64_t position);
extern uint64_t pawn_attack(uint64_t position, bool is_black, uint64_t blockers);

#endif
