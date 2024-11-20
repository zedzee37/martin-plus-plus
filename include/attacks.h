#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdint.h>

extern uint64_t cardinal_slider_attack(uint64_t position, uint64_t blockers);
extern uint64_t orthagonal_slider_attack(uint64_t position, uint64_t blockers);

#endif
