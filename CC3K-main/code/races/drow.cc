#include "drow.h"
#include "../enemy.h"
#include "../enemies/human.h"
#include "../enemies/dwarf.h"
#include "../enemies/elf.h"
#include "../enemies/orc.h"
#include "../enemies/halfling.h"
#include "../enemies/merchant.h"
#include "../dragon.h"

Drow::Drow(int x, int y) : Race{"Drow", 150, 25, 15, 0, x, y} {}

Drow::~Drow() {}
