#include "potion.h"

Potion::Potion(int x, int y, int idx) : Piece{'P', x, y}, idx{idx} {}

int Potion::getIdx() {
    return idx;
}
