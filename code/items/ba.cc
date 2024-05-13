#include "ba.h"
#include "../race.h"

void BA::usePotion(Race &PC) {
    if (PC.getRace() == "Drow") {
        PC.changeAtk(5 * 1.5);
    } else {
        PC.changeAtk(5);
    }
}
 