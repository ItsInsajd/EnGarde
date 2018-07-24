#ifndef CHARACTER_H
#define CHARACTER_H
#include "Utils.h"
#include "Constants.h"

class Character {
  public:
    bool isAlive;
    byte posX;
    byte posY;
    byte moveDelay;
    byte baseHp;
    byte currentHp;
    bool hasLoot;
    bool explosionRound = false;
    byte gold;
    byte dmg;
    byte frozenTimer;

    Character();
    Character(byte _posX, byte _posY, byte _moveDelay, byte _baseHp);
    void changeDirection(short dir);
    byte getTurnCounter();
    virtual void setPosition(byte x, byte y);
    virtual void takeDamage(byte dmg);
    virtual void draw(int x, int y);
    virtual bool doesCollideWithWall(byte x, byte y);
    virtual void takeAction(byte x, byte y);
    virtual void pickLoot();

  protected:
    const Vec directions[4] = { Vec(0, -1), Vec(1, 0), Vec(0, 1), Vec(-1, 0) };
    int moveCounter;
    short moveDir;
    
    Vec getDirection();
    byte subtractHp(byte value);
    void drawLoot(byte x, byte y);
    void defaultAction(Vec dir, int damage);
};

class Player : public Character {
  public:
    short gold;
    byte attackAnimationTime;
    byte hitAnimationTime;
    byte digAnimationTime;
    byte combo = 0;
    byte armor;
    short comboCounter = 0;
    byte comboColor = 0;
    Vec attackPos;
    bool bloodlust;
    bool stress;
    bool godsGrace;
    bool comboGod;
    bool longArms;
    bool shovel;

    Player();
    Player(byte _posX, byte _posY);
    void init();
    void setPosition(byte x, byte y);
    void drawGui();
    void draw(int x, int y);
    void takeAction(byte x, byte y);
    void takeDamage(byte dmg);
    void heal(byte hp);
    bool doesCollideWithWall(byte x, byte y);
    byte calculateDmg();
    void increaseCombo();
    void resetCombo();
    void changeComboColor();
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

class Goblin : public Enemy {
  public:
    Goblin(byte _posX, byte _posY, byte _baseHp);
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

class Golem : public Character {
  public:
    Golem(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
  private:
    byte punchAnimationTime;
    Vec attackDir;
};

class Dwarf : public Character {
  public:
    Dwarf(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
  protected:
    bool moveAfterDig;
    byte digAnimationTime;
    Vec attackDir;
};

class DwarfWarrior : public Dwarf {
  public:
    DwarfWarrior(byte _posX, byte _posY, byte _baseHp);
    void draw(int x, int y);
};

class SkeletonCart : public Character {
  public:
    SkeletonCart(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
  private:
    byte stunTimer;
    Vec attackDir;
};

class BombFrog : public Character {
  public:
    BombFrog(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
    void takeDamage(byte dmg);
  protected:
    byte bombTimer;
    byte explosionTimer;
    bool hasBomb;
    void explode();
};

class BombGoblin : public BombFrog {
  public:
    BombGoblin(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
    void takeDamage(byte dmg);
  private:
    byte stunTimer;
};

class FireRemnant : public Enemy {
  public:
    FireRemnant(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
    void takeDamage(byte dmg);
};

class IceRemnant : public FireRemnant {
  public:
    byte freezeCd;
    IceRemnant(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

class Blob : public Character {
  public:
    Blob(byte _posX, byte _posY, byte _baseHp);
    void takeAction(byte x, byte y);
    void draw(int x, int y);
};

class CursedGhost : public Ghost {
  public:
    CursedGhost(byte _posX, byte _posY, byte _baseHp);
};

extern Player player;

#endif
