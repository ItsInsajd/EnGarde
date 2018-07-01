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
//const String skillNames[] = { "Health up", "Long arms", "Attack up", "Stress", "Bloodlust", "God's grace", "Time wizard" };
//const String skillDesc[] = { "Max HP +1", "Attack range +1", "Dmg +1", "Dmg +2 at last heart", "Kills heal", "Saves from death once", "No cooldown skip" };

class UI {
  public:
    short levelTextTimer;
    bool mainMenuMode = true;
    bool arcadeOpened = false;
    byte mainMenuAnim = 48;
    byte mainMenuSelection = 0;
    byte arcadeSkillSelection = 0;
    byte arcadeOptionSelection = 0;
    byte arcadeRow = 0;

    void showLevelProgressText();
    void showGameOver();
    void showMainMenu();
    void showArcade();
    void shuffleSkills();
    void drawArcade(short x, short y);
  private:
    void arcadeAction();
};

extern UI ui;

#endif