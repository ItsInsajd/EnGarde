#ifndef UI_H
#define UI_H
#include "Gamebuino-Meta.h"

class Skill {
  public:
    byte id;
    char* name;
    char* desc;
    byte cost;
    bool isAvailable;
    Skill(byte id, char* _name, char* _desc, byte _cost);
};

const String menuOptions[] = { "NEW GAME", "TUTORIAL", "CREDITS" };
const byte menuPositions[3][2] = { {25, 10}, {25, 20}, {25, 30} };

class UI {
  public:
    short levelTextTimer;
    bool mainMenuMode = true;
    bool tutorial = false;
    bool arcadeOpened = false;
    bool isPause = false;
    byte mainMenuAnim = 48;
    byte mainMenuSelection = 0;
    byte tutorialTimer = 50;
    byte tutorialCount = 0;
    byte arcadeSkillSelection = 0;
    byte arcadeOptionSelection = 0;
    byte arcadeRow = 0;
    byte availableSkills[3];
    byte shuffleCost = 10;
    
    void showLevelProgressText();
    void showGameOver();
    void showMainMenu();
    void initArcade();
    void showArcade();
    void shuffleSkills();
    void drawArcade(short x, short y);
    void showTutorial();
    void showPauseScreen();

  private:
    void arcadeAction();
    void drawOverlay();
};

extern UI ui;

#endif