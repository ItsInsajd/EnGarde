#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  public:
    int camWidth;
    int camHeight;
    int posX;
    int posY;
    short shake;
    
    void init();
    void setPosition(int _posX, int _posY);
    void moveCamera(int x, int y);
    void shakeScreen(byte value);
    int screenPosX(int v);
    int screenPosY(int v);
    bool isInBounds(byte x, byte y);

  private:
    short worldWidth;
    short worldHeight;
};

extern Camera camera;

#endif
