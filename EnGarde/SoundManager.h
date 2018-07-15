#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include "Gamebuino-Meta.h"

#define COIN 0
#define ENEMY_HIT 1
#define ENEMY_HIT2 2
#define PLAYER_HIT 3
#define PORTAL_OPENED 4
#define HEART 5
#define ARCADE_OFF 6
#define SKILL_UP 7
#define REROLL 8
#define LACK_OF_GOLD 9
#define EXPLOSION 10

class SoundManager {
  public:
    byte track = -1;
    
    void playFX(byte trackNumber);
  private:
    char* tracks[11] = { 
      "coin.wav", 
      "enemyHit.wav", 
      "enemyHit2.wav", 
      "playerHit.wav", 
      "portalOpened.wav", 
      "heart.wav", 
      "arcadeOff.wav", 
      "skillUp.wav", 
      "reroll.wav", 
      "lackOfGold.wav",
      "explosion.wav"
    };
};

extern SoundManager soundManager;

#endif