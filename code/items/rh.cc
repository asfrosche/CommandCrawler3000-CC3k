#include "rh.h"
#include "../race.h"

void RH::usePotion(Race &PC) {
    if (PC.getRace() != "Vampire") {
        int injured = PC.getMaxHP() - PC.getHP();
        if (PC.getRace() == "Drow") {
            if (injured > (10 * 1.5)) {
                PC.changeHP(10 * 1.5);
            } else {
                PC.changeHP(injured);
            }
        } else {
            if (injured > 10) {
                PC.changeHP(10);
            } else {
                PC.changeHP(injured);
            }
        }
    } else {
        PC.changeHP(10);
    }
}
