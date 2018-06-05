#ifndef ASTAR_H
#define ASTAR_H
#include <Gamebuino-Meta.h>
#include "Constants.h"
#include "Utils.h"
#include "World.h"

struct Node {
  short gCost;
  short hCost;
  byte x;
  byte y;
  byte parentX;
  byte parentY;
  Node* parent;
  
  Node();
  ~Node();
  Node(byte _x, byte _y);
};

struct ListElement {
  Node node;
  ListElement* next;
};

class List {
  private:
    ListElement* head;
    ListElement* tail;
    
  public:
    int count;
    
    List();
    ~List();
    void push(Node& node);
    void add(Node& node);
    void removeEl(byte x, byte y);
    Node pop();
    Node getLast();
    bool contains(byte x, byte y);
};

class AStar {
  public:
    Vec getNextTile(Vec start, Vec target);
    Vec findPath(Vec start, Vec target);

  private:
    short GetDistance(Vec vecA, Vec vecB);
};

extern AStar astar;

#endif
