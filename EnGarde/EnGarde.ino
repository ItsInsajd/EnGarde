#include <Gamebuino-Meta.h>
#include <stdlib.h>
#include "Constants.h"
#include "Camera.h"
#include "Character.h"
#include "World.h"
#include "Utils.h"
#include "EnemyManager.h"

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
  Vec exitPos;
  short levelTextTimer;
  
  void drawWorld();
  void enemyMove();
  void advanceTurn(int x, int y);
  void endLevel();
  void loadLevel();
  void showLevelProgressText();
  void showGameOver();
  void cleanUp();
  
  void init() {
    camera.init();
    player.init();
    world.init();
    loadLevel();
  }
  
  void loadLevel() {
    levelTextTimer = 50;
    world.create();
    player.setPosition(world.playerPos.x, world.playerPos.y);
    enemyManager.createEnemies();
    camera.setPosition(player.posX, player.posY);
  }

  void updatePlayer() {
    if (world.enemyCount == 0) {
      endLevel();
    }
  
    if (levelTextTimer > 0 && player.isAlive) {
      showLevelProgressText();
      return;
    } else if (!player.isAlive) {
      showGameOver();
      if (gb.buttons.pressed(BUTTON_A)) {
        cleanUp();
        init();
      }
      return;
    }
  
    world.draw();
    enemyManager.drawEnemies();
    player.draw(camera.screenPosX(player.posX), camera.screenPosY(player.posY));
    player.drawGui();
  
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
    bool canMove = true;
    
    for (int i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemyManager.enemies[i];
  
      if (ch->posX == newX && ch->posY == newY) {
        if (ch->isAlive) {
          canMove = false;
          ch->takeDamage(1);
          player.attackAnimationTime = 3;
          player.attackPos = Vec(camera.screenPosX(newX), camera.screenPosY(newY));
          continue;
        }
        if (ch->hasLoot) ch->pickLoot();
      }
    }
    if (canMove) {
      player.takeAction(x, y);
    }
    
    enemyMove();
  }
  
  void enemyMove() {
    TurnManager::incrementTurn();
    
    for (byte i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemyManager.enemies[i];
      int turnTimer = ch->getTurnCounter();
  
      if (TurnManager::canMove(turnTimer) && ch->isAlive) {
        ch->takeAction(0, 0);
      }
    }
  }
  
  void endLevel() {
    cleanUp();
    loadLevel();
  }
  
  void cleanUp() {
    enemyManager.cleanUpEnemies();
    TurnManager::resetCounter();
  }
  
  void showLevelProgressText() {
    levelTextTimer--;
    gb.display.setColor(BLACK);
    gb.display.fillRect(0, 0, 64, 80);
    gb.display.setCursor(20, 28);
    gb.display.setColor(WHITE);
    String text1 = "LEVEL ";
    String text2 = text1 + world.currentWorld;
    String text3 = text2 + "_";
    String text4 = text3 + world.currentLevel;
    gb.display.print(text4);
  }
  
  void showGameOver() {
    gb.display.setColor(BLACK);
    gb.display.fillRect(0, 0, 64, 80);
    gb.display.setCursor(20, 20);
    gb.display.setColor(WHITE);
    gb.display.print("GAME OVER");
    gb.display.setCursor(5, 36);
    gb.display.print("press A to restart");
  }
};

void setup() {
  randomSeed(analogRead(0));
  gb.begin();
}

void loop() {
  Game::init();
  while(1) {
    while (!gb.update());
    gb.display.clear();

    Game::updatePlayer();
  }
}
