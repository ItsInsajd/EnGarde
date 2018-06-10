#include <Gamebuino-Meta.h>
#include "Constants.h"
#include "Camera.h"

void Camera::init() {
  worldWidth = sprite_size * world_size;
  worldHeight = sprite_size * world_size;
  camWidth = gb.display.width();
  camHeight = gb.display.height();
  setPosition(0, 0);
}

void Camera::setPosition(int x, int y) {
  int nx = (x*sprite_size-camWidth/2);
  int ny = (y*sprite_size-camHeight/2);
    
  posX = CLAMP(nx, 0, world_size-camWidth-1);
  posY = CLAMP(ny, 0, world_size-camHeight-1);
}

void Camera::moveCamera(int x, int y) {
  int nx = (x*sprite_size-posX-camWidth/2);
  int ny = (y*sprite_size-posY-camHeight/2);

  if (nx >= 1) nx = 2;
  if (nx <= -1) nx = -2;
  if (ny >= 1) ny = 2;
  if (ny <= -1) ny = -2;
  posX+=nx;
  posY+=ny;
  posX = CLAMP(posX, 0, worldWidth-camWidth);
  posY = CLAMP(posY, 0, worldWidth-camHeight);
}

bool Camera::isInBounds(byte x, byte y) {
  return x*sprite_size+4 > posX && x*sprite_size+4 < posX + camWidth && y*sprite_size+4 > posY && y*sprite_size+4 < posY + camHeight;
}

int Camera::screenPosX(int v) {
  return v*sprite_size-posX-4;
}

int Camera::screenPosY(int v) {
  return v*sprite_size-posY-4;
}

Camera camera;
