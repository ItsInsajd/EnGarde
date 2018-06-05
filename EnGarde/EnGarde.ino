#include <Gamebuino-Meta.h>
#include <stdlib.h>
#include "Constants.h"
#include "Camera.h"
#include "Character.h"
#include "World.h"
#include "Utils.h"
#include "AStar.h"

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
  Vec exitPos;
  short n;
  
  void drawWorld();
  void drawEnemies();
  void createEnemies();
  void advanceTurn(int x, int y);
  bool isFloorTaken(int x, int y);
  void endLevel();
  
  void init() {
    camera.init();
    world.create();
    player.init();
    player.setPosition(world.playerPos.x, world.playerPos.y);
    createEnemies();
    camera.setPosition(player.posX-camera.camWidth/2, player.posY-camera.camHeight/2);
  }

  void updatePlayer() {
    if (world.enemyCount == 0){
      endLevel();
    }
    
    world.draw();
    drawEnemies();
    player.draw(camera.screenPosX(player.posX), camera.screenPosY(player.posY));
    player.drawHealth();
    
    gb.display.setCursor(0, 9);
    gb.display.print(gb.getFreeRam());
    gb.display.setCursor(0, 18);
    gb.display.print(exitPos.x);
    gb.display.setCursor(0, 27);
    gb.display.print(exitPos.y);
    if (gb.buttons.repeat(BUTTON_UP, 3)) {
      advanceTurn(0, -1);
    }
    if (gb.buttons.repeat(BUTTON_DOWN, 3)) {
      advanceTurn(0, 1);
    }
    if (gb.buttons.repeat(BUTTON_RIGHT, 3)) {
      player.changeDirection(_right);
      advanceTurn(1, 0);
    }
    if (gb.buttons.repeat(BUTTON_LEFT, 3)) {
      player.changeDirection(_left);
      advanceTurn(-1, 0);
    }
  }

  void advanceTurn(int x, int y) {
    if (player.doesCollideWithWall(x, y)) {
      return;
    }
        
    int newX = player.posX + x;
    int newY = player.posY + y;
    
    if (world.world[newX][newY] == 3) {
      for (int i = 0; i < world.maxEnemies; ++i) {
        Character* ch = enemies[i];
        
        if (ch->posX == newX && ch->posY == newY) {
          ch->takeDamage(1);
        }
      }
    } else {
      player.takeAction(x, y);
    }
    
    TurnManager::incrementTurn();
    camera.setPosition(player.posX-camera.camWidth/2, player.posY-camera.camHeight/2);

    for (byte i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemies[i];
      int turnTimer = ch->getTurnCounter();

      if (TurnManager::canMove(turnTimer) && ch->isAlive) {
        exitPos = astar.getNextTile(Vec(ch->posX, ch->posY), Vec(player.posX, player.posY));
        ch->takeAction(exitPos.x, exitPos.y);
      }
    }
  }

  void drawEnemies() {
    for (byte i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemies[i];
      ch->draw(camera.screenPosX(ch->posX)-2, camera.screenPosY(ch->posY));
    }
  }

  void createEnemies() {
    int enemyCount = world.maxEnemies;
    enemies = new Character*[world.maxEnemies];
    
    while (enemyCount > 0) {
      int randX = random(0, world_size);
      int randY = random(0, world_size);
          
      if (world.world[randX][randY] == surface && !isFloorTaken(randX, randY)) {
        --enemyCount;
        enemies[enemyCount] = new Enemy(randX, randY, 2);
        world.world[randX][randY] = 3;
      }
    }
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
