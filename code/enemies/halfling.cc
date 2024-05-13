#include "halfling.h"

Halfling::Halfling(int x, int y) : Enemy{100, 15, 20, randomGold(), 'L', x, y} {}

Halfling::~Halfling() {} 
