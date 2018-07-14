#include <Gamebuino-Meta.h>
#include "World.h"

const uint8_t floorTileBuff[] = {8, 8, 1, 0, 0, 0xFF, 1, 0xb3, 0x33,0x33, 0x3b,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0xb3, 0x33,0x33, 0x3b};
Image floorTile = Image(floorTileBuff);
const uint8_t mineFloorData[] = {8, 8, 1, 0, 0, 0xFF, 1, 0xcc, 0xcc,0xcc, 0xc5,0xcc, 0x5c,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0xcc, 0xcc,0x5c, 0xcc,0xc5, 0xcc,0xcc, 0x5c,0xcc, 0xc5,0xcc, 0xcc,0xcc, 0xcc,0x5c, 0xcc,0xcc, 0xcc,0xcc, 0xcc};
Image mineFloor = Image(mineFloorData);
const uint8_t wallTileBuff[] = {8, 8, 2, 0, 0, 0xFF, 1, 0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55};
Image wallTile = Image(wallTileBuff);
const uint8_t mineWallData[] = {8, 8, 2, 0, 0, 0xFF, 1, 0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0xff, 0xef,0xff, 0xfe,0xfe, 0xff,0xff, 0xf2,0xff, 0xff,0x2f, 0xff,0xff, 0xff,0xe2, 0xff,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44};
Image mineWall = Image(mineWallData);
const uint8_t portalClosedData[] = {8, 8, 1, 0, 0, 0xFF, 1, 0x22, 0x22,0x22, 0x22,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x20, 0x00,0x00, 0x02,0x22, 0x22,0x22, 0x22};
Image portalClosed = Image(portalClosedData);
const uint8_t portalOpenedData[] = {8, 8, 2, 0, 2, 0xFF, 1, 0x00, 0x00,0x00, 0x00,0x00, 0x22,0x22, 0x00,0x02, 0x00,0x00, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x00,0x00, 0x20,0x00, 0x22,0x22, 0x00,0x00, 0x00,0x00, 0x00,0x02, 0x22,0x22, 0x20,0x20, 0x00,0x00, 0x02,0x20, 0x02,0x20, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x20,0x02, 0x02,0x20, 0x02,0x20, 0x02,0x20, 0x00,0x00, 0x02,0x02, 0x22,0x22, 0x20};
Image portalOpened = Image(portalOpenedData);
const uint8_t graveData[] = {8, 8, 1, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0x55,0x55, 0xee,0xe5, 0x66,0x66, 0x5e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x00,0x00, 0x6e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x60,0x06, 0x6e,0xe6, 0x66,0x66, 0x6e};
Image grave = Image(graveData);
const uint8_t crystalData[] = {8, 8, 1, 0, 0, 0x00, 1, 0x00, 0x00,0x20, 0x00,0x00, 0x07,0x20, 0xe2,0x2e, 0x07,0x22, 0x27,0xe2, 0x27,0x22, 0x72,0x27, 0x2e,0x27, 0x20,0x02, 0x7e,0xe2, 0x00,0x00, 0x27,0x20, 0x00,0x02, 0x2e,0x2e, 0x20};
Image crystal = Image(crystalData);

void World::init() {
  currentWorld = 2;
  currentLevel = 0;
}

void World::create() {
  this->updateProgress();
  this->initWorld();
  this->randomize();
  arcadePos = this->randomizeNoBacktrack();
  chestPos = this->randomize();
  playerPos = this->randomize();

  if (playerPos.x == arcadePos.x && playerPos.y == arcadePos.y) {
    arcadePos.x = 99;
    arcadePos.y = 99;
  } else {
    world[arcadePos.x][arcadePos.y] = surfaceWithCharacter;
    for (short i = -1; i <= 1; ++i) {
      for (short j = -1; j <= 1; ++j) {
        if (i == 0 && j == 0) continue;
        if (isInBounds(arcadePos.x+i, arcadePos.y+j)) world[arcadePos.x+i][arcadePos.y+j] = surface;
      }
    }
  }
  
  this->setEnemyCounter();
}

Vec World::randomize() {
  Vec currentPos = Vec((world_size / 2)-1, (world_size / 2)-1);
  
  for (byte i = 0; i < 150; ++i) {
     currentPos = this->moveInDirection(currentPos);
  }

  return currentPos;
}

Vec World::randomizeNoBacktrack() {
  Vec lastPos = Vec((world_size / 2)-1, (world_size / 2)-1);
  Vec currentPos = this->moveInDirection(lastPos);

  for (byte i = 0; i < 50; ++i) {
    lastPos = currentPos;
    currentPos = this->moveInDirectionNoBacktrack(currentPos, lastPos);
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

Vec World::moveInDirectionNoBacktrack(Vec& cur, Vec& last) {
  Vec dir = this->getRandomDirection();
  Vec next = Vec(cur.x+dir.x, cur.y+dir.y);
  Tile t = surface;
  
  if (next != last && cur.x+dir.x > 0 && cur.y+dir.y > 0 && cur.x+dir.x < world_size-1 && cur.y+dir.y < world_size-1) {
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
  
  this->enemyCount = this->maxEnemies;
}

void World::draw() {
  for (short i = 0; i <= world_size; ++i) {
    for (short j = 0; j <= world_size; ++j) {
      int tile = world[i][j];
      if (tile == 2 || tile == 5) {
        drawFloor(i, j);
      } else if (tile == 1 || tile == 4) {
        if (j+1 <= world_size && world[i][j+1] != 1 && world[i][j+1] != 4) {
          if (i-1 > 0 && i+1 < world_size && j-1 > 0 && world[i+1][j] != 1 && world[i+1][j] != 4 && world[i-1][j] != 1 && world[i-1][j] != 4 && world[i][j-1] != 1 && world[i][j-1] != 4) {
            drawFloor(i, j);
            drawObstacle(i, j);
          } else {
            drawWall(i, j, 0);
          }
        } else {
          drawWall(i, j, 1);
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

bool World::isWall(byte x, byte y) {
  return this->world[x][y] == 1 || this->world[x][y] == 4;
}

bool World::isInBounds(short x, short y) {
  return x > 0 && x < world_size && y > 0 && y < world_size;
}

void World::drawWall(byte x, byte y, byte frame) {
  switch(currentWorld) {
    case 1:
      wallTile.setFrame(frame);
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), wallTile);
      break;
    case 2:
      mineWall.setFrame(frame);
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), mineWall);
      break;
    default:
      wallTile.setFrame(frame);
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), wallTile);
      break;
  }
}

void World::drawFloor(byte x, byte y) {
  switch(currentWorld) {
    case 1:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), floorTile);
      break;
    case 2:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), mineFloor);
      break;
    default:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), floorTile);
      break;
  }
}

void World::drawObstacle(byte x, byte y) {
  switch(currentWorld) {
    case 1:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), grave);
      break;
    case 2:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y)-1, crystal);
      break;
    default:
      gb.display.drawImage(camera.screenPosX(x), camera.screenPosY(y), grave);
      break;
  }
}

World world;
