#include "treasure.h"

Treasure::Treasure(int value, int x, int y): Piece{'G', x, y}, value{value} {}

int Treasure::getValue() const { return value; }
