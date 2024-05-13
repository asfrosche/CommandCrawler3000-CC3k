#include "troll.h"
#include "../enemy.h"
#include "../enemies/human.h"
#include "../enemies/dwarf.h"
#include "../enemies/elf.h"
#include "../enemies/orc.h"
#include "../enemies/halfling.h"
#include "../enemies/merchant.h"
#include "../dragon.h"

Troll::Troll(int x, int y) : Race{"Troll", 120, 25, 25, 0, x, y} {}

Troll::~Troll() {} 
