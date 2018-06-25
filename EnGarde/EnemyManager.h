#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "Character.h"

class EnemyManager {
  public:
    Character **enemies;
    Vec* floors;
  
    void createEnemies();
    bool isFloorTaken(int x, int y);
    void drawEnemies();
    void cleanUpEnemies();
};

extern EnemyManager enemyManager;

#endif
