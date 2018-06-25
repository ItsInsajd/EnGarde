#include "Utils.h"

Vec::Vec() { }

Vec::Vec(short _x, short _y) {
  x = _x;
  y = _y;
}

short Utils::nextValue(short value, short maxValue) {
  return value+1 <= maxValue ? value+1 : 0;
}

void Utils::shuffleArray(Vec arr[], short len) {
  for (short i = 0; i < len; ++i) {
    short rng = random(0, len);
    Vec temp = arr[rng];
    arr[rng] = arr[i];
    arr[i] = temp;
  }
}
