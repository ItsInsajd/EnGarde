#include "AStar.h"
#include <Gamebuino-Meta.h>

Node::Node() {
  this->gCost = 0;
  this->hCost = 0;
}

Node::~Node() {
  //delete parent;
}

Node::Node(byte _x, byte _y) {
  this->x = _x;
  this->y = _y;
  this->gCost = 0;
  this->hCost = 0;
}

List::List() {
  head = NULL;
  tail = NULL;  
}

List::~List() {
  ListElement* temp;
  while(head) {
    temp = head;
    head = temp->next;
    delete temp;
  }
}

void List::push(Node& node) {
  ListElement* temp = new ListElement();
  temp->node = node;

  if (head == NULL) {
    temp->next = NULL;
    head = temp;
    tail = temp;
    temp = NULL;
  } else {
    temp->next = head;
    head = temp;
  }

  count++;
}

void List::add(Node& node) {
  ListElement* temp = new ListElement();
  temp->node = node;

  if (head == NULL) {
    temp->next = NULL;
    head = temp;
    tail = temp;
    temp = NULL;
  } else {
    tail->next = temp;
    tail = temp;
  }
  
  count++;
}

void List::removeEl(byte x, byte y) {
  ListElement* temp = head;
  ListElement* last = NULL;

  while(temp) {
    Node current = temp->node;

    if (current.x == x && current.y == y) {
      if (last == NULL) {
        head = temp->next;
      } else if (temp->next == NULL) {
        tail = last;
      } else {
        last->next = temp->next;
      }
      
      delete temp;
      count--;
      break;
    }
    
    last = temp;
    temp = temp->next;
  }
}

Node List::pop() {
  ListElement* temp = head;
  Node data = head->node;
  head = temp->next;
  delete temp;
  count--;
  
  return data;
}

Node List::getLast() {
  return tail->node;
}

bool List::contains(byte x, byte y) {
  ListElement* temp = head;
  
  while(temp) {
    Node current = temp->node;

    if (current.x == x && current.y == y) {
      return true;
    }
    temp = temp->next;
  }

  return false;
}

short AStar::GetDistance(Vec vecA, Vec vecB) {
    return abs(vecB.x - vecA.x) + abs(vecB.y - vecA.y);
}

Vec AStar::getNextTile(Vec start, Vec target, bool dontCheckTile) {
  Node bestN = Node(99, 99);
  bestN.hCost = 999;
  Node current = Node(start.x, start.y);
  
  for (short x = -1; x <= 1; x++) {
    for (short y = -1; y <= 1; y++) {
      if ((x == 0 && y == 0) || ((abs(x) + abs(y)) == 2)) {
        continue;
      }
      
      short checkX = current.x + x;
      short checkY = current.y + y;

      if (checkX >= 0 && checkX < world_size && checkY >= 0 && checkY < world_size) {
        if (dontCheckTile || world.world[checkX][checkY] == 2) {
          if (world.world[checkX][checkY] < 3) {
            auto currentHCost = this->GetDistance(Vec(checkX, checkY), target);
        
            if (bestN.hCost > currentHCost) {
              bestN = Node(checkX, checkY);
              bestN.hCost = currentHCost;
            }
          }
        }
      }
    }
  }

  return Vec(bestN.x, bestN.y);
}

Vec AStar::findPath(Vec start, Vec target) {
  List openSet = List();
  List closedSet = List();
  auto startNode = Node(start.x, start.y);
  Node current;
  openSet.push(startNode);
  short z = 0;
  
  while(openSet.count > 0) {
    z++;
    current = openSet.pop();
    closedSet.push(current);
    
    if (current.x == target.x && current.y == target.y) {
      break;
    }
    
    Node neighbours[4];
    byte dirLen = 0;
    
    for (short x = -1; x <= 1; x++) {
      for (short y = -1; y <= 1; y++) {
        if ((x == 0 && y == 0) || (abs(x) + abs(y)) == 2) {
          continue;
        }
        
        short checkX = current.x + x;
        short checkY = current.y + y;

        if (checkX >= 0 && checkX < world_size && checkY >= 0 && checkY < world_size) {
          if (world.world[checkX][checkY] == 2) {
            neighbours[dirLen] = Node(checkX, checkY);
            dirLen++;
          }
        }
      }
    }

    if (dirLen == 0) {
      return Vec(99, 99);
    }
    
    for (byte i = 0; i < dirLen; ++i) {
      auto neighbour = neighbours[i];

      if (closedSet.contains(neighbour.x, neighbour.y)) {
        continue;
      }
      auto costToNeighbour = current.gCost + 1;

      if (!openSet.contains(neighbour.x, neighbour.y)) {
        neighbour.gCost = costToNeighbour;
        neighbour.hCost = this->GetDistance(Vec(neighbour.x, neighbour.y), target);
        neighbour.parentX = current.x;
        neighbour.parentY = current.y;
        openSet.add(neighbour);
      } else {
        if (costToNeighbour < neighbour.gCost) {
          openSet.removeEl(neighbour.x, neighbour.y);
          neighbour.gCost = costToNeighbour;
          openSet.add(neighbour);
        } 
      }
    }
    if (z > 50) {
      return Vec(99, 99);
    }
  }  

  //auto node = closedSet.pop();
  
  return Vec(current.parentX, current.parentY);
}

AStar astar;
