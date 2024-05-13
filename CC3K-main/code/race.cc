#include "race.h"
#include "enemy.h"
#include "dragon.h"
#include <cmath>

Race::Race(std::string race, int hp, double atk, double def, int gold, int x, int y)
			: Character{hp, atk, def, gold, '@', x, y},
             race{race}, maxHP{hp}, defaultAtk{atk}, defaultDef{def} {}

// Return the default attack
double Race::getDefaultAtk() const { return defaultAtk; }

// Return the default defense
double Race::getDefaultDef() const { return defaultDef; }

// Changes the attack of a race character 
void Race::changeAtk(double amt) {
    atk += amt;
}

// Changes the defence of a race character 
void Race::changeDef(double amt) {
    def += amt;
}

// Returns max HP of a particular race
int Race::getMaxHP() const {
    return maxHP;
}

void Race::resetStats() {
    changeAtk(-getAtk() + getDefaultAtk());
    changeDef(-getDef() + getDefaultDef());
}

// Returns the char race of a given race 
std::string Race::getRace() const {
    return race;
}

// Returns the chamber that race is in
int Race::getChamber() {
    return chamber;
}

// Change the chamber that race is in
void Race::changeChamber(int number) {
    chamber = number;
}

// The default player character race is a shade4 that has starting stats (125 HP, 25 Atk, 25 Def). However, players have the option 
// of choosing an alternate (but no less heroic) race: drow (150 HP, 25 Atk , 15 Def, all potions have their effect magniﬁed by 
// 1.5), vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP), troll (120 HP, 25 Atk, 
// 15 Def, regains 5 HP every turn; HP is capped at 120 HP), and goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain 
// enemy).
void Race::attack(Enemy &E) {
    if (getRace() == "Vampire") {
        if (E.getType() == 'W') {
            defaultAttack(E);
            changeHP(-5);
        } else if(E.getType() == 'L') {
            int oldHP = E.getHP();
            halfChanceAttack(E);
            int newHP = E.getHP();
            if(oldHP - newHP) {
                changeHP(5);
            }
        } else {
            defaultAttack(E);
            changeHP(+5);
        }
    } else if (E.getType() == 'M'){
            defaultAttack(E);
            E.setHostile(true); 
    } else if (E.getType() == 'L') {
            halfChanceAttack(E);
    } else {
        defaultAttack(E);
    }
}

void Race::attack(Dragon &D) {
    int damage = ceil((100 * getAtk())/(100 + D.getDef())) ;
    D.changeHP(-damage); 
}

Race::~Race() {}
