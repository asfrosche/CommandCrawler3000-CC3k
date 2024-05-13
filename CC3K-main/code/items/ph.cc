#include "ph.h"
#include "../race.h"

void PH::usePotion(Race &PC) {
    if (PC.getRace() == "Drow") {
        if (PC.getHP() > (10 * 1.5))  {
            PC.changeHP(-10 * 1.5);
          } else {
            PC.changeHP(-(PC.getHP()));
        }
    } else {
        if (PC.getHP() > 10) {
            PC.changeHP(-10);
        } else {
           PC.changeHP(-(PC.getHP()));
        }
    }
} 
