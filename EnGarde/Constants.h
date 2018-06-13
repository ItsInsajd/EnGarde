#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H
#include <Gamebuino-Meta.h>

const byte sprite_size = 8;
const byte max_enemies = 20;
const int world_size = 20;

enum Tile {
  wall = 1,
  surface = 2,
  character = 3,
  wallWithCharacter = 4,
  surfaceWithCharacter = 5
};

enum Direction {
  _left = -1,
  _right = 1
};

template <typename T> T CLAMP(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
}

#endif
