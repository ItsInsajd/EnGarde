#include "EnemyManager.h"
#include "World.h"
#include "Camera.h"
#include "Utils.h"

EnemyManager::EnemyManager() {
  
}

void EnemyManager::createEnemies() {
  enemyCount = world.maxEnemies;

  if (world.chestPos.x != world.playerPos.x && world.chestPos.y != world.playerPos.y
    && world.chestPos.x != world.arcadePos.x && world.chestPos.y != world.arcadePos.y) {
    enemyCount--;
    enemies[world.maxEnemies-1] = new Chest(world.chestPos.x, world.chestPos.y);
    world.world[world.chestPos.x][world.chestPos.y] = world.world[world.chestPos.x][world.chestPos.y] + 3;
  } else {
    world.enemyCount++;
  }

  floors = new Vec[world.floorCount];
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
  
  for (byte i = 0; i < enemyCount; ++i) {
    while (isFloorTaken(floors[floorCounter].x, floors[floorCounter].y)) {
      floorCounter++;
    }

    Vec pos = floors[floorCounter];
    
    if (i == enemyCount-1 && world.currentLevel == 4) {
      enemies[i] = new Necromancer(pos.x, pos.y, 6);
    } else {
      spawnGraveyardEnemies(pos, i);
    }

    world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
    floorCounter++;
  }
  
  delete [] floors;
}

void EnemyManager::spawnGraveyardEnemies(Vec pos, byte i) {
  byte enemyType = random(0, 5);

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
}

bool EnemyManager::isFloorTaken(byte x, byte y) {
  for (short i = -1; i <= 1; ++i) {
    for (short j = -1; j <= 1; ++j) {
      if (player.posX+i == x && player.posY+j == y) {
        return true;
      }
    }
  }

  if (world.chestPos.x == x && world.chestPos.y == y) {
    return true;
  }

  if (world.arcadePos.x == x && world.arcadePos.y == y) {
    return true;
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
}

EnemyManager enemyManager;

