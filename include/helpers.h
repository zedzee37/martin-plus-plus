#pragma once

#define PIECE_COUNT 12

#define RIGHT_EDGE 0x8080808080808080ULL
#define LEFT_EDGE 0x0101010101010101ULL
#define TOP_EDGE 0xFF
#define BOTTOM_EDGE 0xFF00000000000000

#define IS_ON_RIGHT_EDGE(pos) ((pos) & RIGHT_EDGE)
#define IS_ON_LEFT_EDGE(pos) ((pos) & LEFT_EDGE)
#define IS_ON_TOP_EDGE(pos) ((pos) & TOP_EDGE)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & BOTTOM_EDGE)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))
