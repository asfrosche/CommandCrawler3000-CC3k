#ifndef _POTION_H_
#define _POTION_H_
#include "piece.h"
class Race;

class Potion: public Piece {
  int idx;
  public:
    Potion(int x, int y, int idx = -1);
    int getIdx();
};

#endif
