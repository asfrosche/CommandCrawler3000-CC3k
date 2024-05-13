#include "bd.h"
#include "../race.h"

void BD::usePotion(Race &PC) {
    if (PC.getRace() == "Drow") {
        PC.changeDef(5 * 1.5);
    } else {
        PC.changeDef(5);
    }
}
