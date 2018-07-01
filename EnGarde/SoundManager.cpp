#include "SoundManager.h"

void SoundManager::playFX(byte trackNumber) {
  if (track != -1) {
    gb.sound.stop(track);
  }

  track = gb.sound.play(tracks[trackNumber], false);
}

SoundManager soundManager;