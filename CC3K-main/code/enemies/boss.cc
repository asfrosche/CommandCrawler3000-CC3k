#include "boss.h"

Boss::Boss(int x, int y) : Enemy{100, 20, 30, randomGold(), 'W', x, y} {}

Boss::~Boss() {}
