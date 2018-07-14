#include <Gamebuino-Meta.h>
#include "Constants.h"
#include "Camera.h"

void Camera::init() {
  worldWidth = sprite_size * world_size;
  worldHeight = sprite_size * world_size;
  camWidth = gb.display.width();
  camHeight = gb.display.height();
  shake = 0;
}

void Camera::setPosition(int x, int y) {
  int nx = (x*sprite_size-camWidth/2);
  int ny = (y*sprite_size-camHeight/2);
    
  posX = CLAMP(nx, 0, worldWidth-camWidth);
  posY = CLAMP(ny, 0, worldWidth-camHeight);
  effectivePosX = posX;
  effectivePosY = posY;
}

void Camera::moveCamera(int x, int y) {
  int nx = (x*sprite_size-posX-camWidth/2);
  int ny = (y*sprite_size-posY-camHeight/2);

  if (nx >= 1) nx = 2;
  if (nx <= -1) nx = -2;
  if (ny >= 1) ny = 2;
  if (ny <= -1) ny = -2;
    
  shake = shake * -1 * 0.9;
  
  int baseX = posX + nx;
  int baseY = posY + ny;
  posX = CLAMP(baseX, 0, worldWidth-camWidth);
  posY = CLAMP(baseY, 0, worldWidth-camHeight);
  
  int effX = posX + shake;
  int effY = posY + shake;
  effectivePosX = CLAMP(effX, 0, worldWidth-camWidth);
  effectivePosY = CLAMP(effY, 0, worldWidth-camHeight);
}

void Camera::shakeScreen(byte value) {
  shake = value;
}

bool Camera::isInBounds(byte x, byte y) {
  return x*sprite_size+4 > posX && x*sprite_size+4 < posX + camWidth && y*sprite_size+4 > posY && y*sprite_size+4 < posY + camHeight;
}

int Camera::screenPosX(int v) {
  return v*sprite_size-effectivePosX-4;
}

int Camera::screenPosY(int v) {
  return v*sprite_size-effectivePosY-4;
}

Camera camera;
