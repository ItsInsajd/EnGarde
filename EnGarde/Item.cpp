#include "Item.h"

Item::Item(byte x, byte y) {
  posX = x;
  posY = y;
}

void Item::use() { }

void Item::draw() { }

Coin::Coin(byte x, byte y) : Item(x, y) { }

void Coin::use() {
  
}

