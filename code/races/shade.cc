#include "shade.h"
#include "../enemy.h"
#include "../enemies/human.h"
#include "../enemies/dwarf.h"
#include "../enemies/elf.h"
#include "../enemies/orc.h"
#include "../enemies/halfling.h"
#include "../enemies/merchant.h"
#include "../dragon.h"

Shade::Shade(int x, int y) : Race{"Shade", 125, 25, 25, 0, x, y} {}

Shade::~Shade() {}
