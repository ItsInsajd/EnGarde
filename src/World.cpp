#include <Gamebuino-Meta.h>
#include "World.h"

const uint8_t floorTileBuff[] = {8, 8, 1, 0, 1, 0xFF, 1, 0x56, 0x66,0x66, 0x65,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x56, 0x66,0x66, 0x65};
Image floorTile = Image(floorTileBuff);
const uint8_t wallTileBuff[] = {8, 8, 2, 0, 0, 0xFF, 1, 0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xff,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55,0x55, 0x55};
Image wallTile = Image(wallTileBuff);

void World::create() {
  this->initWorld();
  this->randomize();
  this->randomize();
  this->randomize();
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
  this->maxEnemies = count / 25;

  if (maxEnemies >= max_enemies) {
    maxEnemies = max_enemies-1;
  }
  
  this->enemyCount = this->maxEnemies;
}

void World::draw() {
  for (byte i = camera.posX; i <= camera.posX+camera.camWidth; ++i) {
    for (byte j = camera.posY; j <= camera.posY+camera.camHeight; ++j) {
        int tile = world[i][j];

        if (tile != 1) {
          gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), floorTile);
        } else if (tile == 1) {
          if (world[i][j+1] != 1) {
            wallTile.setFrame(0);
          } else if (world[i][j+1] == 1) {
            wallTile.setFrame(1);
          }
          gb.display.drawImage(camera.screenPosX(i), camera.screenPosY(j), wallTile);
        }
    }
  }

  //gb.display.setColor(YELLOW);
  //gb.display.fillTriangle(camera.screenPosX(world.playerPos.x)+sprite_size/2, camera.screenPosY(0), camera.screenPosX(world.playerPos.x), camera.screenPosY(world.playerPos.y)+sprite_size/2, camera.screenPosX(world.playerPos.x)+sprite_size, camera.screenPosY(world.playerPos.y)+sprite_size/2);
}

World world;
