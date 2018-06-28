#include <Gamebuino-Meta.h>
#include "World.h"

const uint8_t floorTileBuff[] = {8, 8, 1, 0, 0, 0xFF, 1, 0xb3, 0x33,0x33, 0x3b,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0xb3, 0x33,0x33, 0x3b};
Image floorTile = Image(floorTileBuff);
const uint8_t wallTileBuff[] = {8, 8, 2, 0, 0, 0xFF, 1, 0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55};
Image wallTile = Image(wallTileBuff);
const uint8_t portalClosedData[] = {8, 8, 1, 0, 0, 0xFF, 1, 0x22, 0x22,0x22, 0x22,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x22, 0x22,0x22, 0x22};
Image portalClosed = Image(portalClosedData);
const uint8_t portalOpenedData[] = {8, 8, 2, 0, 2, 0xFF, 1, 0x00, 0x00,0x00, 0x00,0x00, 0x22,0x22, 0x00,0x02, 0x00,0x00, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x00,0x00, 0x20,0x00, 0x22,0x22, 0x00,0x00, 0x00,0x00, 0x00,0x02, 0x22,0x22, 0x20,0x20, 0x00,0x00, 0x02,0x20, 0x02,0x20, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x02,0x20, 0x02,0x20, 0x00,0x00, 0x02,0x02, 0x22,0x22, 0x20};
Image portalOpened = Image(portalOpenedData);
const uint8_t graveData[] = {8, 8, 1, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0x55,0x55, 0xee,0xe5, 0x66,0x66, 0x5e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x00,0x00, 0x6e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x66,0x66, 0x6e};
Image grave = Image(graveData);

void World::init() {
  currentWorld = 1;
  currentLevel = 0;
}

void World::create() {
  this->updateProgress();
  this->initWorld();
  this->randomize();
  this->randomize();
  chestPos = this->randomize();
  playerPos = this->randomize();
  this->setEnemyCounter();
}

Vec World::randomize() {
  Vec currentPos = Vec((world_size / 2)-1, (world_size / 2)-1);
  
  for (byte i = 0; i < 150; ++i) {
     currentPos = this->moveInDirection(currentPos);
  }

  return currentPos;
}

void World::initWorld() {
  Tile w = wall;
  for (byte i = 0; i < world_size+1; ++i) {
    for (byte j = 0; j < world_size+1; ++j) {
      world[i][j] = w;
    }
  }
}

Vec World::moveInDirection(Vec& cur) {
  Vec dir = this->getRandomDirection();
  Tile t = surface;
  
  if (cur.x+dir.x > 0 && cur.y+dir.y > 0 && cur.x+dir.x < world_size-1 && cur.y+dir.y < world_size-1) {
    cur.x += dir.x;
    cur.y += dir.y;

    this->world[cur.x][cur.y] = t;
  }

  return cur;
}

Vec World::getRandomDirection() {
  byte rnd = random(0, 4);

  return this->directions[rnd];
}

void World::setEnemyCounter() {
  Tile s = surface;
  int count = 0;
  
  for (byte i = 0; i < world_size+1; ++i) {
    for (byte j = 0; j < world_size+1; ++j) {
      if (world[i][j] == s) {
        count++;      
      }
    }
  }
  this->floorCount = count;
  this->maxEnemies = floorCount/25 + currentWorld * 2 + currentLevel +1;

  if (maxEnemies >= max_enemies) {
    maxEnemies = max_enemies-1;
  }
  
  this->enemyCount = this->maxEnemies - 1;
}

void World::draw() {
  for (byte i = 0; i <= world_size; ++i) {
    for (byte j = 0; j <= world_size; ++j) {
      int tile = world[i][j];
      if (!camera.isInBounds(i, j)) {
        //continue;
      }
      if (tile == 2 || tile == 5) {
        gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), floorTile);
      } else if (tile == 1 || tile == 4) {
        if (world[i][j+1] != 1 && world[i][j+1] != 4) {
          if (i > 0 && j > 0 && i < world_size && j < world_size && world[i+1][j] != 1 && world[i+1][j] != 4 && world[i-1][j] != 1 && world[i-1][j] != 4 && world[i][j-1] != 1 && world[i][j-1] != 4) {
            gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), floorTile);
            gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j)-2, grave);
          } else {
            wallTile.setFrame(0);
            gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), wallTile);
          }
        } else {
          wallTile.setFrame(1);
          gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), wallTile);
        }
      }
    }
  }
  if (enemyCount > 0) {
    gb.display.drawImage(camera.screenPosX(playerPos.x), camera.screenPosY(playerPos.y), portalClosed);
  } else {
    gb.display.drawImage(camera.screenPosX(playerPos.x), camera.screenPosY(playerPos.y), portalOpened);
  }
}

void World::updateProgress() {
  currentLevel++;

  if (currentLevel > 4) {
    currentLevel = 1;
    currentWorld++;
  }
}

World world;
