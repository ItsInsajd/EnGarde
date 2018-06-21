#ifndef CHARACTER_H
#define CHARACTER_H
#include "Utils.h"

class Character {
  public:
    bool isAlive;
    byte posX;
    byte posY;
    byte moveDelay;
    byte baseHp;
    byte currentHp;
    
    Character();
    Character(byte _posX, byte _posY, byte _moveDelay, byte _baseHp);
    void setPosition(byte x, byte y);
    void takeDamage(byte dmg);
    void changeDirection(byte dir);
    byte getTurnCounter();
    virtual void draw(int x, int y);
    virtual bool doesCollideWithWall(byte x, byte y);
    virtual void takeAction(byte x, byte y);

  protected:
    const Vec directions[4] = { Vec(0, -1), Vec(1, 0), Vec(0, 1), Vec(-1, 0) };
    int moveCounter;
    byte moveDir;

    Vec getDirection();
};

class Player : public Character {
  public:  
    Player();
    Player(byte _posX, byte _posY);
    void init();
    void drawHealth();
    void draw(int x, int y);
    void takeAction(byte x, byte y);
    bool doesCollideWithWall(byte x, byte y);
};

class Enemy : public Character {
  public:
    Enemy(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

class Skull : public Character {
  public:
    Skull(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

class BloodSkull : public Skull {
  public:
    BloodSkull(byte _posX, byte _posY, byte _baseHp);
    void draw(int x, int y);
};

class Ghost : public Enemy {
  public:
    Ghost(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

class Rat : public Character {
  public:
    Vec currentDir;
    Rat(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

extern Player player;

#endif
