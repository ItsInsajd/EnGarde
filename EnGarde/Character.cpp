#include <Gamebuino-Meta.h>
#include "Character.h"
#include "Constants.h"
#include "World.h"
#include "AStar.h"

const byte playerSpriteRightBuff[] = {8, 10, 2, 0, 2, 0x0E, 1, 0xee, 0x77,0x77, 0xee,0xee, 0x70,0x70, 0xee,0xec, 0x77,0x77, 0xee,0xcc, 0xd7,0x7e, 0xe0,0xcd, 0x1d,0xde, 0x0e,0xec, 0xd1,0x00, 0xee,0xec, 0xdd,0xde, 0xee,0xee, 0xde,0xde, 0xee,0xee, 0x1e,0x1e, 0xee,0xee, 0x0e,0x0e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x77, 0xee,0xee, 0x70,0x70, 0xee,0xec, 0x77,0x77, 0xee,0xcc, 0xd7,0x7e, 0xe0,0xcd, 0x1d,0xde, 0x0e,0xec, 0xd1,0x00, 0xee,0xec, 0xdd,0xde, 0xee,0xee, 0x1d,0x1e, 0xee,0xee, 0x0e,0x0e, 0xee};
Image playerSpriteRight = Image(playerSpriteRightBuff);
const uint8_t playerSpriteLeftBuff[] = {8, 10, 2, 0, 2, 0x0E, 1, 0xee, 0x77,0x77, 0xee,0xee, 0x07,0x07, 0xee,0xee, 0x77,0x77, 0xce,0x0e, 0xe7,0x7d, 0xcc,0xe0, 0xed,0xd1, 0xdc,0xee, 0x00,0x1d, 0xce,0xee, 0xed,0xdd, 0xce,0xee, 0xed,0xed, 0xee,0xee, 0xe1,0xe1, 0xee,0xee, 0xe0,0xe0, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x77, 0xee,0xee, 0x07,0x07, 0xee,0xee, 0x77,0x77, 0xce,0x0e, 0xe7,0x7d, 0xcc,0xe0, 0xed,0xd1, 0xdc,0xee, 0x00,0x1d, 0xce,0xee, 0xed,0xdd, 0xce,0xee, 0xe1,0xd1, 0xee,0xee, 0xe0,0xe0, 0xee};
Image playerSpriteLeft = Image(playerSpriteLeftBuff);
const uint8_t enemySprRightBuff[] = {8, 8, 2, 0, 2, 0x0E, 1, 0xee, 0xee,0x99, 0x9e,0xee, 0xe2,0x97, 0x97,0xee, 0x22,0x99, 0x9e,0xee, 0x28,0x28, 0xee,0xee, 0xe2,0x80, 0x00,0xee, 0xe8,0x88, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0x99, 0x9e,0xee, 0xe2,0x97, 0x97,0xee, 0x22,0x99, 0x9e,0xee, 0x28,0x28, 0xee,0xee, 0xe2,0x80, 0x00,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee};
Image enemySprRight = Image(enemySprRightBuff);
const uint8_t enemySprLeftBuff[] = {8, 8, 2, 0, 2, 0x0E, 1, 0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xee, 0x99,0x92, 0x2e,0xee, 0xe8,0x28, 0x2e,0xe0, 0x00,0x82, 0xee,0xee, 0xe8,0x88, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xee, 0x99,0x92, 0x2e,0xee, 0xe8,0x28, 0x2e,0xe0, 0x00,0x82, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xe2,0xe2, 0xee};
Image enemySprLeft = Image(enemySprLeftBuff);
const uint8_t enemyCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe9,0x99, 0xee,0xee, 0x29,0x79, 0x7e,0xe2, 0x89,0x99, 0x2e,0xe8, 0x22,0x82, 0x8e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x99,0x9e, 0xee,0xe7, 0x97,0x92, 0xee,0xe2, 0x99,0x98, 0x2e,0xe8, 0x28,0x22, 0x8e};
Image enemyCorpse = Image(enemyCorpseBuff);
const uint8_t skullRightBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x76,0x77, 0x7e,0xe7, 0x60,0x07, 0x00,0xe6, 0x70,0x07, 0x00,0xee, 0x77,0x70, 0x7e,0xee, 0xe7,0xe7, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x77,0x76, 0xee,0xe7, 0x77,0x67, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xe6, 0x77,0x70, 0x7e,0xee, 0x77,0x77, 0xee,0xee, 0xe7,0xe7, 0xee};
Image skullRight = Image(skullRightBuff);
const uint8_t skullLeftBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0xe7, 0x77,0x67, 0x7e,0x00, 0x70,0x06, 0x7e,0x00, 0x70,0x07, 0x6e,0xe7, 0x07,0x77, 0xee,0xee, 0x7e,0x7e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x67,0x77, 0xee,0xe7, 0x76,0x77, 0x7e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x06, 0x7e,0xe7, 0x07,0x77, 0x6e,0xee, 0x77,0x77, 0xee,0xee, 0x7e,0x7e, 0xee};
Image skullLeft = Image(skullLeftBuff);
const uint8_t skullCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x70, 0xee,0xe7, 0x07,0x67, 0x7e,0xe0, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xee, 0x06,0x70, 0x7e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x70, 0xee,0xe7, 0x07,0x67, 0x7e,0xe0, 0x70,0x07, 0x00,0xe7, 0x60,0x07, 0x00,0xee, 0x06,0x70, 0x7e};
Image skullCorpse = Image(skullCorpseBuff);
const uint8_t bloodskullRightBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x78,0x77, 0x7e,0xe7, 0x80,0x07, 0x00,0xe8, 0x70,0x07, 0x00,0xee, 0x78,0x70, 0xee,0xee, 0xe8,0xe8, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe8, 0x87,0x87, 0x7e,0xe7, 0x70,0x07, 0x00,0xe7, 0x80,0x07, 0x00,0xe8, 0x78,0x70, 0x7e,0xee, 0x78,0x77, 0xee,0xee, 0xe8,0xe8, 0xee};
Image bloodskullRight = Image(bloodskullRightBuff);
const uint8_t bloodskullLeftBuff[] = {8, 8, 4, 0, 2, 0x0E, 1, 0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0xe7, 0x77,0x87, 0x7e,0x00, 0x70,0x08, 0x7e,0x00, 0x70,0x07, 0x8e,0xee, 0x07,0x87, 0xee,0xee, 0x8e,0x8e, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x87,0x78, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x07, 0x7e,0x00, 0x70,0x08, 0x7e,0xe7, 0x07,0x87, 0x8e,0xee, 0x77,0x87, 0xee,0xee, 0x8e,0x8e, 0xee};
Image bloodskullLeft = Image(bloodskullLeftBuff);
const uint8_t bloodskullCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x08,0x70, 0xee,0xe8, 0x87,0x87, 0x7e,0xe0, 0x80,0x07, 0x00,0xe7, 0x88,0x07, 0x00,0xee, 0x08,0x70, 0x8e,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0x07,0x80, 0xee,0xe7, 0x78,0x78, 0x8e,0x00, 0x70,0x08, 0x0e,0x00, 0x70,0x88, 0x7e,0xe8, 0x07,0x80, 0xee};
Image bloodskullCorpse = Image(bloodskullCorpseBuff);
const uint8_t ghostRightBuff[] = {8, 8, 4, 0, 5, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xde,0xce, 0xce,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xed,0xcc, 0xee,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0x7c, 0x7e,0xee, 0xdc,0xcc, 0xce,0xee, 0xdc,0xcc, 0xce,0xee, 0xde,0xce, 0xce,0xee, 0xee,0xee, 0xee};
Image ghostRight = Image(ghostRightBuff);
const uint8_t ghostLeftBuff[] = {8, 8, 4, 0, 5, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xce,0xce, 0xde,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0xcc,0xcc, 0xde,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xec,0xec, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0xcd, 0xee,0xee, 0xcc,0xcc, 0xde,0xee, 0x7c,0x7c, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xcc,0xcc, 0xde,0xee, 0xce,0xce, 0xde,0xee, 0xee,0xee, 0xee};
Image ghostLeft = Image(ghostLeftBuff);
const uint8_t ghostCorpseBuff[] = {8, 8, 2, 0, 0, 0x0E, 1, 0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xec,0x7e, 0xee,0xee, 0x7c,0xcc, 0xee,0xe1, 0xcc,0xdc, 0xde,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xee,0xee, 0xe7,0xce, 0xee,0xee, 0xcc,0xc7, 0xee,0xed, 0xcd,0xcc, 0x1e};
Image ghostCorpse = Image(ghostCorpseBuff);

Character::Character() {}

Character::Character(byte _posX, byte _posY, byte _moveDelay, byte _baseHp) {
  this->posX = _posX;
  this->posY = _posY;
  this->moveDelay = _moveDelay;
  this->moveCounter = _moveDelay;
  this->isAlive = true;
  this->baseHp = _baseHp;
  this->currentHp = _baseHp;
  this->moveDir = _right;
}

void Character::setPosition(byte x, byte y) {
  this->posX = x;
  this->posY = y;
}

void Character::draw(int x, int y) {
  gb.display.setColor(GREEN);
  gb.display.fillRect(x, y, sprite_size, sprite_size);
}

void Character::takeDamage(byte dmg) {
  if (currentHp - dmg) {
    currentHp -= dmg;
  } else {
    currentHp = 0;
    isAlive = false;
    world.enemyCount--;
    world.world[posX][posY] = world.world[posX][posY] - 3;
  }
}

void Character::changeDirection(byte dir) {
  this->moveDir = dir;
}

byte Character::getTurnCounter() {
  return moveDelay;
}

void Character::takeAction(byte x, byte y) { }

bool Character::doesCollideWithWall(byte x, byte y) {
  byte newX = posX + x;
  byte newY = posY + y;
  
  return world.world[newX][newY] != 2;
}

Vec Character::getDirection() {
  byte counter = 0;
  Vec possibleDirs[4];
  
  for (byte i = 0; i < sizeof(directions)/sizeof(directions[0]); ++i) {
    Vec dir = directions[i];
    
    if (!this->doesCollideWithWall(dir.x, dir.y)) {
      possibleDirs[counter] = dir;
      counter++;
    }
  }
  byte rnd = random(counter);

  return possibleDirs[rnd];
}

Player::Player() { }

Player::Player(byte _posX, byte _posY)
  : Character(_posX, _posY, 0, 3) {}

void Player::init() {
  this->moveDelay = 1;
  this->moveCounter = 0;
  this->isAlive = true;
  this->baseHp = 3;
  this->currentHp = 3;
}

void Player::takeAction(byte x, byte y) {
  posX += x;
  posY += y;
}

void Player::draw(int x, int y) {
  if (this->moveDir == _right) {
    gb.display.drawImage(x, y-4, playerSpriteRight);
  } else {
    gb.display.drawImage(x, y-4, playerSpriteLeft);
  }
}

void Player::drawHealth() {
  gb.display.setColor(RED);
  
  for (byte i = 0; i < currentHp; i++) {
    gb.display.setCursor(i+1+3*i, 1); 
    gb.display.print("\3");
  }
}

bool Player::doesCollideWithWall(byte x, byte y) {
  byte newX = posX + x;
  byte newY = posY + y;
  
  return world.world[newX][newY] == 1 || world.world[newX][newY] == 4;
}

Enemy::Enemy(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 2, _baseHp) { }

void Enemy::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, enemySprRight);
    } else {
      enemyCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, enemySprLeft);
    } else {
      enemyCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, enemyCorpse);
    }
  }
}
  
void Enemy::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = astar.getNextTile(Vec(posX, posY), Vec(player.posX, player.posY), false);

  if (dir.x-posX != 0) {
    this->changeDirection(dir.x-posX);
  }
  
  if (dir.x == player.posX && dir.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = dir.x;
    posY = dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

Skull::Skull(byte _posX, byte _posY, byte _baseHp)
  : Character(_posX, _posY, 2, _baseHp) { }

void Skull::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, skullRight);
    } else {
      skullCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, skullCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, skullLeft);
    } else {
      skullCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, skullCorpse);
    }
  }
}
  
void Skull::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = getDirection();

  if (dir.x != 0) {
    this->changeDirection(dir.x);
  }
  
  if (dir.x+posX == player.posX && dir.y+posY == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX += dir.x;
    posY += dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

BloodSkull::BloodSkull(byte _posX, byte _posY, byte _baseHp)
  : Skull(_posX, _posY, _baseHp) {
  this->moveDelay = 1;    
}

void BloodSkull::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, bloodskullRight);
    } else {
      bloodskullCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, bloodskullCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, bloodskullLeft);
    } else {
      bloodskullCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, bloodskullCorpse);
    }
  }
}

Ghost::Ghost(byte _posX, byte _posY, byte _baseHp)
  : Enemy(_posX, _posY, _baseHp) { }

void Ghost::draw(int x, int y) {
  if (this->moveDir == _right) {
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, ghostRight);
    } else {
      ghostCorpse.setFrame(0);
      gb.display.drawImage(x+2, y-2, ghostCorpse);
    }
  } else {    
    if(this->isAlive) {
      gb.display.drawImage(x+1, y-2, ghostLeft);
    } else {
      ghostCorpse.setFrame(1);
      gb.display.drawImage(x+2, y-2, ghostCorpse);
    }
  }
}
  
void Ghost::takeAction(byte x, byte y) {
  if(!isAlive) {
    return;
  }
  Vec dir = astar.getNextTile(Vec(posX, posY), Vec(player.posX, player.posY), true);

  if (dir.x-posX != 0) {
    this->changeDirection(dir.x-posX);
  }
  
  if (dir.x == player.posX && dir.y == player.posY) {
    player.takeDamage(1);
  } else {
    world.world[posX][posY] = world.world[posX][posY] - 3;
    posX = dir.x;
    posY = dir.y;
    world.world[posX][posY] = world.world[posX][posY] + 3;
  }
}

Player player;
