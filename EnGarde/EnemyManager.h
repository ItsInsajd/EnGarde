#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "Character.h"

class EnemyManager {
  public:
    byte enemyCount;
    byte hardEnemyCount;
    Character *enemies[max_enemies];
    Vec* floors;
  
    EnemyManager();
    void createEnemies();
    bool isFloorTaken(byte x, byte y);
    void drawEnemies();
    void cleanUpEnemies();
    void explosion(byte posX, byte posY, byte sameId);
    void spawnGraveyardEnemies(Vec pos, byte i);
    void spawnMineEnemies(Vec pos, byte i);
    void spawnCryptEnemies(Vec pos, byte i);
};

extern EnemyManager enemyManager;

#endif
