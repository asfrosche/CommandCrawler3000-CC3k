#ifndef ORC_H
#define ORC_H
#include "../enemy.h"

class Orc: public Enemy {
 public:
    Orc(int x, int y);
    virtual ~Orc(); 
};

#endif
