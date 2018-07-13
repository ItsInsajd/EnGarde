#include "Utils.h"

Vec::Vec() { }

Vec::Vec(short _x, short _y) {
  x = _x;
  y = _y;
}

bool Vec::operator==(const Vec& b) {
  Vec vec; 

  return vec.x == b.x && vec.y == b.y;
}

bool Vec::operator!=(const Vec& b) {
  Vec vec; 

  return !(vec.x != b.x && vec.y != b.y);
}