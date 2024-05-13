#include "vampire.h"
#include "../enemy.h"
#include "../enemies/human.h"
#include "../enemies/dwarf.h"
#include "../enemies/elf.h"
#include "../enemies/orc.h"
#include "../enemies/halfling.h"
#include "../enemies/merchant.h"
#include "../dragon.h"

Vampire::Vampire(int x, int y) : Race{"Vampire", 50, 25, 25, 0, x, y} {}

Vampire::~Vampire() {} 
