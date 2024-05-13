#include "enemy.h"
#include "race.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>

bool Enemy::hostile = false;

Enemy::Enemy(int hp, double atk, double def, int gold, char type, int x, int y)
			: Character{hp, atk, def, gold, type, x, y}, moved{false} {}

// Function to return a random drop of golds value 
//  (small/normal hoard with 50% chance each)
int Enemy::randomGold() {
    const int smallHoard = 1;
    const int normalHoard = 2;
    int chance = rand() % 2;
    if (chance == 0) { 
        return smallHoard;
    } else {
        return normalHoard;
    }
}
bool Enemy::isHostile() {
    return hostile;
}

void Enemy::setHostile(bool update) {
    hostile = update;
}

bool Enemy::hasMoved() { return moved; }

void Enemy::setMoved(bool update) { moved = update; }

// Enemies can be one of human (140 HP, 20 Atk, 20 Def, drops 2 normal piles of gold), dwarf (100 HP, 20 Atk, 30 Def, 
// Vampires are allergic to dwarves and lose 5 HP rather than gain), elf (140 HP, 30 Atk, 10 Def, gets two attacks against every 
// race except drow), orcs (180 HP, 30 Atk, 25 Def, does 50% more damage to goblins), Enemy (30 HP, 70 Atk, 5 Def), dragon 
// (150 HP, 20 Atk, 20 Def, always guards a treasure hoard), and halﬂing (100 HP, 15 Atk, 20 Def, has a 50% chance to cause 
// the player character to miss in combat, i.e. takes priority over player character’s ability to never miss).
void Enemy::attack(Race &PC) {
    if (getType() == 'E') {
        if (PC.getRace() == "Drow") {
            halfChanceAttack(PC);
        } else {
            halfChanceAttack(PC);
            halfChanceAttack(PC);
        }
    } else if (getType() == 'O') {
        if (PC.getRace() == "Goblin") {
            int chance = rand() % 2;
            if (chance == 0) {
                PC.changeHP(-ceil((100 * 1.5 * getAtk()/(100 + PC.getDef())) ));
            }
        } else {
             halfChanceAttack(PC);
        }  
    } else if (getType() == 'M') {
            halfChanceAttack(PC);
    }
    else {
        halfChanceAttack(PC);
    }
}

Enemy::~Enemy() {} 

