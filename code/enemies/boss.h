#ifndef BOSS_H
#define BOSS_H
#include "../enemy.h"

class Boss: public Enemy {
 public:
    Boss(int x, int y);
    virtual ~Boss(); 
};
 
#endif
