#include "elf.h"

Elf::Elf(int x, int y) : Enemy{140, 30, 10, randomGold(), 'E', x, y} {}

Elf::~Elf() {} 
