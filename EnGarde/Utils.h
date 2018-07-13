#ifndef UTILS_H
#define UTILS_H
#include <Gamebuino-Meta.h>

struct Vec {
  public:
    short x;
    short y;

    Vec();
    Vec(short _x, short _y);
    bool operator==(const Vec& b);
    bool operator!=(const Vec& b);
};

namespace Utils {
  template <typename T>
  void shuffleArray(T* arr, size_t size) {
    for (short i = 0; i < size; ++i) {
      short rng = random(0, size);
      T temp = arr[rng];
      arr[rng] = arr[i];
      arr[i] = temp;
    }
  }
};

#endif
