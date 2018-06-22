#ifndef ITEM_H
#define ITEM_H
#include <Gamebuino-Meta.h>

class Item {
  public:
    Item(byte x, byte y);
    byte posX;
    byte posY;
    virtual void use();
    
  protected:
    byte animationFrame;
    virtual void draw(byte x, byte y);
};

class Coin {
  public:
    Coin(byte x, byte y);
    void use();

  protected:
    void draw();
};

#endif
