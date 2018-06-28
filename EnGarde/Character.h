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
    bool hasLoot;
    byte gold;
    
    Character();
    Character(byte _posX, byte _posY, byte _moveDelay, byte _baseHp);
    void setPosition(byte x, byte y);
    void changeDirection(byte dir);
    byte getTurnCounter();
    void drawLoot(byte x, byte y);
    virtual void takeDamage(byte dmg);
    virtual void draw(int x, int y);
    virtual bool doesCollideWithWall(byte x, byte y);
    virtual void takeAction(byte x, byte y);
    virtual void pickLoot();

  protected:
    const Vec directions[4] = { Vec(0, -1), Vec(1, 0), Vec(0, 1), Vec(-1, 0) };
    int moveCounter;
    byte moveDir;
    
    Vec getDirection();
};

class Player : public Character {
  public:
    short gold;
    byte attackAnimationTime;
    byte hitAnimationTime;
    Vec attackPos;
    
    Player();
    Player(byte _posX, byte _posY);
    void init();
    void drawGui();
    void draw(int x, int y);
    void takeAction(byte x, byte y);
    void takeDamage(byte dmg);
    bool doesCollideWithWall(byte x, byte y);
};

class Chest : public Character {
  public:
    byte content;
    Chest(byte _posX, byte _posY);
    void draw(int x, int y);
    void takeDamage(byte dmg);
    void pickLoot();
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

class Necromancer : public Character {
  public:
    bool charge;
    byte chargeAnim;
    Necromancer(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
    void drawLaser();
};

extern Player player;

#endif
