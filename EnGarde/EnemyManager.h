#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "Character.h"

class EnemyManager {
  public:
    byte enemyCount;
    Character *enemies[max_enemies];
    Vec* floors;
  
    EnemyManager();
    void createEnemies();
    bool isFloorTaken(byte x, byte y);
    void drawEnemies();
    void cleanUpEnemies();
    void spawnGraveyardEnemies(Vec pos, byte i);
    void spawnMineEnemies(Vec pos, byte i);
};

extern EnemyManager enemyManager;

#endif
