#ifndef WORLD_H
#define WORLD_H
#include "Utils.h"
#include "Constants.h"
#include "Camera.h"

class World {
  public:
    byte world[world_size+1][world_size+1];
    int floorCount;
    byte maxEnemies;
    short enemyCount;
    Vec playerPos;
    Vec chestPos;
    Vec arcadePos;
    int currentWorld;
    int currentLevel;
    void init();
    void create();
    void draw();
    void start();
    bool isWall(byte x, byte y);
    bool isInBounds(short x, short y);
    bool isInEyeSightX(Vec source, Vec target);
    bool isInEyeSightY(Vec source, Vec target);

  private:
    const Vec directions[4] = { Vec(0, -1), Vec(1, 0), Vec(0, 1), Vec(-1, 0) };
    
    void initWorld();
    Vec randomize();
    Vec moveInDirection(Vec& cur);
    Vec getRandomDirection();
    Vec randomizeNoBacktrack();
    Vec moveInDirectionNoBacktrack(Vec& cur, Vec& last);
    void setEnemyCounter();
    void updateProgress();
    void drawWall(byte x, byte y, byte frame);
    void drawFloor(byte x, byte y);
    void drawObstacle(byte x, byte y);
};

extern World world;

#endif
