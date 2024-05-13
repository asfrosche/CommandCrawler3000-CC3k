#include "goblin.h"
#include "../enemy.h"
#include "../enemies/human.h"
#include "../enemies/dwarf.h"
#include "../enemies/elf.h"
#include "../enemies/orc.h"
#include "../enemies/halfling.h"
#include "../enemies/merchant.h"
#include "../dragon.h"

Goblin::Goblin(int x, int y) : Race{"Goblin", 110, 15, 20, 0, x, y} {}

Goblin::~Goblin() {}
