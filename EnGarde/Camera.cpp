#include <Gamebuino-Meta.h>
#include "Constants.h"
#include "Camera.h"

void Camera::init() {
  camWidth = gb.display.width() / sprite_size;
  camHeight = gb.display.height() / sprite_size;
  setPosition(0, 0);
}

void Camera::setPosition(int _posX, int _posY) {
  posX = CLAMP(_posX, 0, world_size-camWidth-1);
  posY = CLAMP(_posY, 0, world_size-camHeight-1);
}

void Camera::moveCamera(int x, int y) {
  posX = CLAMP(posX + x, 0, world_size-camWidth);
  posY = CLAMP(posY + y, 0, world_size-camHeight);
}

int Camera::screenPosX(int v) {
  return (v-posX)*sprite_size-4;
}

int Camera::screenPosY(int v) {
  return (v-posY)*sprite_size-4;
}

Camera camera;
