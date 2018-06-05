#ifndef WORLD_H
#define WORLD_H
#include "Utils.h"
#include "Constants.h"
#include "Camera.h"

class World {
  public:
    void draw();
    byte world[world_size+1][world_size+1]; //take note if worlds are smaller with byte
    int floorCount;
    byte maxEnemies;
    byte enemyCount;
    Vec playerPos;
    
    void create();
    
  private:
    const Vec directions[4] = { Vec(0, -1), Vec(1, 0), Vec(0, 1), Vec(-1, 0) };
    
    void initWorld();
    Vec randomize();
    Vec moveInDirection(Vec& cur);
    Vec getRandomDirection();
    void setEnemyCounter();
};

extern World world;

#endif
