#include "dragon.h"
#include "race.h"

Dragon::Dragon(std::pair<int,int> hoardLocation, int x, int y) 
            : Character(150, 20, 20, 0, 'D', x, y), 
            hoardLocation{hoardLocation} {}

std::string checkPC() {
    std::string ans;
    //i wanted to make this in sync
    // with what we have implemented in the original checkPC
    return ans;
}

void Dragon::attack(Race &PC) { 
    halfChanceAttack(PC); 
}

void Dragon::setHoardLoc(std::pair<int, int> loc) { hoardLocation = loc; }

std::pair<int, int> Dragon::getHoardLoc() { return hoardLocation; }

Dragon::~Dragon() {}
