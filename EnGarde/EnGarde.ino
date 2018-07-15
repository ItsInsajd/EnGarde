#include <Gamebuino-Meta.h>
#include "Constants.h"
#include "Camera.h"
#include "Character.h"
#include "World.h"
#include "Utils.h"
#include "EnemyManager.h"
#include "UI.h"
#include "SoundManager.h"

namespace TurnManager {
  int turnCounter = 0;
  byte turnMaxTime = 25;
  byte turnTime = 25;

  void resetCounter() {
    turnCounter = 0;
  }
  
  void incrementTurn() {
    turnCounter++;
  }

  void drawTime() {
    gb.display.setColor(WHITE);
    for (byte i = 0; i < turnTime / 5; ++i) {
      gb.display.fillRect(77, 1+i*2, 2, 2);
    }
  }

  void resetTurnTime() {
    turnTime = turnMaxTime;
  }

  bool updateTurnTime() {
    turnTime--;
    drawTime();

    if (turnTime == 0) {
      turnTime = turnMaxTime;
      return true;
    }
    return false;
  }
  
  bool canMove(int timer) {
    return turnCounter % timer ? false : true;
  }
};

namespace Game {
  int seed = 0;
  void enemyMove();
  void advanceTurn(int x, int y);
  void endLevel();
  void loadLevel();
  void cleanUp();
  void backToMainMenu();
  void fixOffScreenEnemy(Character& ch);
  void draw();

  void init() {
    camera.init();
    player.init();
    world.init();
    ui.initArcade();
    loadLevel();
  }
  
  void loadLevel() {
    ui.levelTextTimer = 50;
    ui.shuffleSkills();
    world.create();
    player.setPosition(world.playerPos.x, world.playerPos.y);
    enemyManager.createEnemies();
    camera.setPosition(player.posX, player.posY);
  }

  void updatePlayer() {
    if (player.posX == world.playerPos.x && player.posY == world.playerPos.y && world.enemyCount <= 0) {
      if (ui.tutorial) {
        backToMainMenu();
        return;
      } else {
        endLevel();
      }
    }
    if (ui.levelTextTimer > 0 && player.isAlive) {
      ui.showLevelProgressText();
      return;
    }
    if (ui.isPause) {
      ui.showPauseScreen();
      if (gb.buttons.pressed(BUTTON_A)) {
        ui.isPause = false;
      } else if (gb.buttons.pressed(BUTTON_B)) {
        ui.isPause = false;
        backToMainMenu();
      }
      return;
    }

    draw();

    if (!player.isAlive) {
      ui.showGameOver();
      if (gb.buttons.pressed(BUTTON_A)) {
        cleanUp();
        init();
      }
      return;
    }
    if (ui.arcadeOpened) {
      ui.showArcade();
      return;
    }

    if (TurnManager::turnCounter > 0) {
      if (TurnManager::updateTurnTime()) {
        player.resetCombo();
        enemyMove();
      }
    }

    if (gb.buttons.repeat(BUTTON_UP, 5)) {
      advanceTurn(0, -1);
    } else if (gb.buttons.repeat(BUTTON_DOWN, 5)) {
      advanceTurn(0, 1);
    } else if (gb.buttons.repeat(BUTTON_RIGHT, 5)) {
      player.changeDirection(_right);
      advanceTurn(1, 0);
    } else if (gb.buttons.repeat(BUTTON_LEFT, 5)) {
      player.changeDirection(_left);
      advanceTurn(-1, 0);
    } else if (gb.buttons.pressed(BUTTON_B)) {
      TurnManager::resetTurnTime();
      enemyMove();
    }
    if (gb.buttons.pressed(BUTTON_MENU)) {
      ui.isPause = true;
    }

    camera.moveCamera(player.posX, player.posY);
  }
  
  void advanceTurn(int x, int y) {
    if (player.posX+x == world.arcadePos.x && player.posY+y == world.arcadePos.y) {
      if (world.enemyCount > 0) {
        soundManager.playFX(ARCADE_OFF);
        enemyMove();
        return;
      } else {
        ui.arcadeOpened = true;
        return;
      }
    }
    if (player.doesCollideWithWall(x, y)) {
      return;
    }

    TurnManager::resetTurnTime();
    Vec newPos = Vec(player.posX + x, player.posY + y);
    Vec longArmsPos = Vec(player.posX + x*2, player.posY + y*2);
    bool canMove = true;
    
    for (int i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemyManager.enemies[i];
  
      if (ch->posX == newPos.x && ch->posY == newPos.y || (player.longArms && ch->posX == longArmsPos.x && ch->posY == longArmsPos.y)) {
        if (ch->isAlive && world.world[ch->posX][ch->posY] != wallWithCharacter) {
          canMove = false;
          ch->takeDamage(player.calculateDmg());
          player.attackAnimationTime = 3;
          player.attackPos = Vec(camera.screenPosX(newPos.x), camera.screenPosY(newPos.y));
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
    player.changeComboColor();

    for (byte i = 0; i < world.maxEnemies; ++i) {
      Character* ch = enemyManager.enemies[i];
      int turnTimer = ch->getTurnCounter();
      fixOffScreenEnemy((*ch));

      if (TurnManager::canMove(turnTimer)) {
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

  void backToMainMenu() {
    cleanUp();
    ui.tutorial = false;
    ui.tutorialTimer = 50;
    ui.tutorialCount = 0;
    ui.mainMenuAnim = 48;
    ui.mainMenuMode = true;
  }

  void fixOffScreenEnemy(Character& ch) {
    if (!world.isInBounds(ch.posX, ch.posY)) {
      ch.setPosition(world.chestPos.x, world.chestPos.y);
    }
  }

  void draw() {
    world.draw();
    ui.drawArcade(camera.screenPosX(world.arcadePos.x), camera.screenPosY(world.arcadePos.y)-2);
    enemyManager.drawEnemies();
    player.draw(camera.screenPosX(player.posX), camera.screenPosY(player.posY));
    player.drawGui();
    /*gb.display.setCursor(0, 9);
    gb.display.print(gb.getFreeRam());
    gb.display.setCursor(0, 18);
    gb.display.print(enemyManager.enemyCount);
    gb.display.setCursor(0, 27);
    gb.display.print(world.enemyCount);
    gb.display.setCursor(0, 36);
    gb.display.print(camera.shake);*/
  }
};

void setup() {
  gb.pickRandomSeed();
  //Game::seed = analogRead(0);
  //randomSeed(Game::seed);
  gb.begin();
}

void loop() {
  while(1) {
    while (!gb.update());
    gb.display.clear();

    if (ui.mainMenuMode) {
      ui.showMainMenu();
    } else if (ui.tutorial) {
      Game::init();
      while(1) {
        while (!gb.update());
        gb.display.clear();

        Game::updatePlayer();
        ui.showTutorial();
        if (ui.mainMenuMode) break;
      }
    } else {
      Game::init();
      while(1) {
        while (!gb.update());
        gb.display.clear();

        Game::updatePlayer();
        if (ui.mainMenuMode) break;
      }
    }
  }
}
