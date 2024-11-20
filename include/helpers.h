#ifndef HELPERS_H
#define HELPERS_H

#define IS_ON_RIGHT_EDGE(pos) ((pos) & 0x8080808080808080ULL)
#define IS_ON_LEFT_EDGE(pos) ((pos) & 0x0101010101010101ULL)
#define IS_ON_TOP_EDGE(pos) ((pos) & 0xFF)
#define IS_ON_BOTTOM_EDGE(pos) ((pos) & 0xFF00000000000000)
#define IS_ON_EDGE(pos) (IS_ON_RIGHT_EDGE(pos) || IS_ON_LEFT_EDGE(pos) || IS_ON_TOP_EDGE(pos) || IS_ON_BOTTOM_EDGE(pos))

#endif
