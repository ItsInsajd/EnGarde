#ifndef UTILS_H
#define UTILS_H
#include <Gamebuino-Meta.h>

struct Vec {
  public:
    short x;
    short y;

    Vec();
    Vec(short _x, short _y);
};

namespace Utils {
  short nextValue(short value, short maxValue);
  void shuffleArray(Vec arr[], short len);
}

#endif
