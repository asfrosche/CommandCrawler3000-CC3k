#ifndef DRAGONHOARD_H
#define DRAGONHOARD_H
#include "../treasure.h"
#include <memory>

class Dragon;

class DragonHoard: public Treasure {
    int value;
  public:
    DragonHoard(int x, int y);
};

#endif
