#include "EnemyManager.h"
#include "World.h"
#include "Camera.h"
#include "Utils.h"

EnemyManager::EnemyManager() {
  
}

void EnemyManager::createEnemies() {
  enemyCount = world.enemyCount;

  floors = new Vec[world.floorCount];
  short count = 0;
  bool hasChest = world.chestPos.x != world.playerPos.x && world.chestPos.y != world.playerPos.y && world.chestPos.x != world.arcadePos.x && world.chestPos.y != world.arcadePos.y;
  
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
    
    if (i == enemyCount-2 && world.currentLevel == 4) {
      enemies[i] = new Necromancer(pos.x, pos.y, 6);
      world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
    } else if (i == enemyCount-1 && hasChest) {
      world.enemyCount--;
      enemies[world.maxEnemies-1] = new Chest(world.chestPos.x, world.chestPos.y);
      world.world[world.chestPos.x][world.chestPos.y] = world.world[world.chestPos.x][world.chestPos.y] + 3;
    } else {
      if (world.currentWorld == 1) {
        spawnGraveyardEnemies(pos, i);
      } else if (world.currentWorld == 2) {
        spawnMineEnemies(pos, i);
      } else {
        spawnGraveyardEnemies(pos, i);
      }
    }
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
  world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
}

void EnemyManager::spawnMineEnemies(Vec pos, byte i) {
  byte enemyType = random(0, 5);
  byte golemsAmount = 2 + world.currentLevel / 2;

  if (enemyType == 0) {
    if (golemsAmount > 0) {
      enemies[i] = new Golem(pos.x, pos.y, 5);
      golemsAmount--;
    } else {
      enemies[i] = new Skull(pos.x, pos.y, 1);
    }
  } else if (enemyType == 1) {
    if (random(0,4) == 0) {
      enemies[i] = new DwarfWarrior(pos.x, pos.y, 5);
    } else {
      enemies[i] = new Dwarf(pos.x, pos.y, 3);
    }
  } else if (enemyType == 2) {
    enemies[i] = new SkeletonCart(pos.x, pos.y, 2);
  } else if (enemyType == 3) {
    enemies[i] = new BombFrog(pos.x, pos.y, 1);
  } else {
    enemies[i] = new BloodSkull(pos.x, pos.y, 1);
  }
  world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
}

bool EnemyManager::isFloorTaken(byte x, byte y) {
  for (short i = -1; i <= 1; ++i) {
    for (short j = -1; j <= 1; ++j) {
      if (player.posX+i == x && player.posY+j == y) {
        return true;
      }
    }
  }

  if (world.chestPos.x == x && world.chestPos.y == y) return true;
  if (world.arcadePos.x == x && world.arcadePos.y == y) return true;
  
  return false;
}

void EnemyManager::drawEnemies() {
  for (byte i = 0; i < world.maxEnemies; ++i) {
    Character* ch = enemies[i];
    ch->draw(camera.screenPosX(ch->posX), camera.screenPosY(ch->posY));
  }
}

void EnemyManager::cleanUpEnemies() {
  for (int i = 0; i < world.maxEnemies; ++i) {
    delete enemies[i];
  }
}

void EnemyManager::explosion(byte posX, byte posY, byte sameId) {
    for (byte i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemies[i];
      
      if (ch->isAlive && ch->posX >= posX-1 && ch->posX <= posX+1 && ch->posY >= posY-1 && ch->posY <= posY+1) {
        ch->takeDamage(1);
      }
    }
  }

EnemyManager enemyManager;

