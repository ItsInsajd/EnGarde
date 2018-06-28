#include "EnemyManager.h"
#include "World.h"
#include "Camera.h"
#include "Utils.h"

void EnemyManager::createEnemies() {
  byte enemyCount = world.maxEnemies - 1;
  floors = new Vec[world.floorCount];
  enemies = new Character*[world.maxEnemies];
  short count = 0;
  
  for (byte i = 0; i < world_size+1; ++i) {
    for (byte j = 0; j < world_size+1; ++j) {
      if (world.world[i][j] == surface) {
        floors[count].x = i;
        floors[count].y = j;
        count++;
      }
    }
  }

  Utils::shuffleArray(floors, world.floorCount);
  byte floorCounter = 0;

  if (world.currentLevel == 4) {
    enemyCount--;
    Vec pos = floors[floorCounter];
    enemies[enemyCount] = new Necromancer(pos.x, pos.y, 6);
    world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
    floorCounter++;
  }
  
  for (byte i = 0; i < enemyCount; ++i) {
    byte enemyType = random(0, 5);

    if ((floors[floorCounter].x == player.posX && floors[floorCounter].y == player.posY) || (floors[floorCounter].x == world.chestPos.x && floors[floorCounter].y == world.chestPos.y)) {
      floorCounter++;
    }

    Vec pos = floors[floorCounter];
    
    if (enemyType == 0) {
        enemies[i] = new Skull(pos.x, pos.y, 1);
    } else if (enemyType == 1) {
      enemies[i] = new Enemy(pos.x, pos.y, 2);
    } else if (enemyType == 2) {
      enemies[i] = new BloodSkull(pos.x, pos.y, 1);
    } else if (enemyType == 3) {
      enemies[i] = new Ghost(pos.x, pos.y, 1);
    } else {
      enemies[i] = new Rat(pos.x, pos.y, 2);
    }
    world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
    floorCounter++;
  }

  enemies[world.maxEnemies-1] = new Chest(world.chestPos.x, world.chestPos.y);
  world.world[world.chestPos.x][world.chestPos.y] = world.world[world.chestPos.x][world.chestPos.y] + 3;

  delete [] floors;
}

bool EnemyManager::isFloorTaken(int x, int y) {
  if (player.posX == x && player.posY == y) {
    return true;
  }

  for (int i = 0; i < world.floorCount; ++i) {
    if (enemies[i]->posX == x && enemies[i]->posY == y) {
      return true;
    }
  }

  return false;
}

void EnemyManager::drawEnemies() {
  for (byte i = 0; i < world.maxEnemies; ++i) {
    Character* ch = enemies[i];
    ch->draw(camera.screenPosX(ch->posX) - 2, camera.screenPosY(ch->posY));
  }
}

void EnemyManager::cleanUpEnemies() {
  for (int i = 0; i < world.maxEnemies; ++i) {
    delete enemies[i];
  }
  delete [] enemies;
}

EnemyManager enemyManager;

