#include "wd.h"
#include "../race.h"

void WD::usePotion(Race &PC) {
    if (PC.getRace() == "Drow") {
        if (PC.getDef() >= (5 * 1.5)) {
            PC.changeDef(-5 * 1.5);
        } else {
            PC.changeDef(-(PC.getDef()));
        }
    } else {
        if (PC.getDef() >= 5) {
            PC.changeDef(-5);
        } else {
            PC.changeDef(-(PC.getDef()));
        }
    }
}
