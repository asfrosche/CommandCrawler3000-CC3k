#include "wa.h"
#include "../race.h"

void WA::usePotion(Race &PC) {
    if (PC.getRace() == "Drow") {
        if (PC.getAtk() >= (5 * 1.5)) {
            PC.changeAtk(-5 * 1.5); // can be made a const AmplifyPotion = 1.5
        } else {
            PC.changeAtk(-(PC.getAtk()));
        }
    } else {
        if (PC.getAtk() >= 5) {
            PC.changeAtk(-5);
        } else {
            PC.changeAtk(-(PC.getAtk()));
        }
    }
}
