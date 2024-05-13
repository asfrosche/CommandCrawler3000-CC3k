#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
class Race;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy: public Character {
    static bool hostile;
    bool moved;
  public:
    Enemy(int hp, double atk, double def, int gold, char type, int x, int y);
    static void setHostile(bool update);
    static bool isHostile();
    int randomGold();
    void attack(Race &PC);
    void setMoved(bool update);
    bool hasMoved();
    virtual ~Enemy();
};

#endif
