#include <Gamebuino-Meta.h>
#include <stdlib.h>
#include "Constants.h"
#include "Camera.h"
#include "Character.h"
#include "World.h"
#include "Utils.h"

namespace TurnManager {
  int turnCounter = 0;
  
  void resetCounter() {
    turnCounter = 0;
  }
  
  void incrementTurn() {
    turnCounter++;
  }
  
  bool canMove(int timer) {
    return turnCounter % timer ? false : true;
  }
};

namespace Game {
Character **enemies;
Vec* floors;
Vec exitPos;
short n;

void drawWorld();
void drawEnemies();
void createEnemies();
void enemyMove();
void advanceTurn(int x, int y);
bool isFloorTaken(int x, int y);
void endLevel();

void init() {
  camera.init();
  world.create();
  player.init();
  player.setPosition(world.playerPos.x, world.playerPos.y);
  createEnemies();
  camera.setPosition(player.posX, player.posY);
}

void updatePlayer() {
  if (world.enemyCount == 0) {
    endLevel();
  }

  world.draw();
  drawEnemies();
  player.draw(camera.screenPosX(player.posX), camera.screenPosY(player.posY));
  player.drawHealth();

  gb.display.setCursor(0, 9);
  gb.display.print(gb.getFreeRam());

  if (gb.buttons.repeat(BUTTON_UP, 5)) {
    advanceTurn(0, -1);
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 5)) {
    advanceTurn(0, 1);
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 5)) {
    player.changeDirection(_right);
    advanceTurn(1, 0);
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 5)) {
    player.changeDirection(_left);
    advanceTurn(-1, 0);
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    enemyMove();
  }
  camera.moveCamera(player.posX, player.posY);
}

void advanceTurn(int x, int y) {
  if (player.doesCollideWithWall(x, y)) {
    return;
  }

  int newX = player.posX + x;
  int newY = player.posY + y;

  if (world.world[newX][newY] == 3 || world.world[newX][newY] == 5) {
    for (int i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemies[i];

      if (ch->posX == newX && ch->posY == newY) {
        ch->takeDamage(1);
      }
    }
  } else {
    player.takeAction(x, y);
  }

  enemyMove();
}

void enemyMove() {
  TurnManager::incrementTurn();
  
  for (byte i = 0; i < world.maxEnemies; ++i) {
    Character* ch = enemies[i];
    int turnTimer = ch->getTurnCounter();

    if (TurnManager::canMove(turnTimer) && ch->isAlive) {
      ch->takeAction(0, 0);
    }
  }
}

void drawEnemies() {
  for (byte i = 0; i < world.maxEnemies; ++i) {
    Character* ch = enemies[i];
    ch->draw(camera.screenPosX(ch->posX) - 2, camera.screenPosY(ch->posY));
  }
}

void createEnemies() {
  byte enemyCount = world.maxEnemies;
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
  for (byte i = 0; i < world.maxEnemies; ++i) {
    byte enemyType = random(0, 4);

    if (floors[floorCounter].x == player.posX && floors[floorCounter].y == player.posY) {
      floorCounter++;
    }

    Vec pos = floors[floorCounter];
    
    if (enemyType == 0) {
        enemies[i] = new Skull(pos.x, pos.y, 1);
      } else if (enemyType == 1) {
        enemies[i] = new Enemy(pos.x, pos.y, 2);
      } else if (enemyType == 2) {
        enemies[i] = new BloodSkull(pos.x, pos.y, 1);
      } else {
        enemies[i] = new Ghost(pos.x, pos.y, 1);
      }
    world.world[pos.x][pos.y] = world.world[pos.x][pos.y] + 3;
    floorCounter++;
  }

  delete [] floors;
}

bool isFloorTaken(int x, int y) {
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

void endLevel() {
  for (int i = 0; i < world.maxEnemies; ++i) {
    delete enemies[i];
  }
  delete enemies;
  TurnManager::resetCounter();
  init();
}
};

void setup() {
  randomSeed(analogRead(0));
  gb.begin();
}

void loop() {
  Game::init();
  while (1) {
    while (!gb.update());
    gb.display.clear();

    Game::updatePlayer();
  }
}
