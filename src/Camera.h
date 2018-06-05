#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  public:
    byte camWidth;
    byte camHeight;
    byte posX;
    byte posY;

    void init();
    void setPosition(int _posX, int _posY);
    void moveCamera(int x, int y);
    int screenPosX(int v);
    int screenPosY(int v);
};

extern Camera camera;

#endif
