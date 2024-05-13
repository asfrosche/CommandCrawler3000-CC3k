#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "piece.h"

class Treasure: public Piece {
    int value;
  public:
    Treasure(int value, int x, int y);
    int getValue() const;
};

#endif
