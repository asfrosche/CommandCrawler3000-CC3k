#include "character.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

Character::Character(int hp, double atk, double def, int gold, char type, int x, int y)
                    : Piece{type, x, y}, hp{hp}, gold{gold}, atk{atk}, def{def} {}

// Returns the remaining HP of given Character
int Character::getHP() const { return hp; }

// Returns the attack power of given Character
double Character::getAtk() const { return atk; }

// Returns the defence power of given Character
double Character::getDef() const { return def; }

// Updates the gold of given Character
void Character::addGold(int amt) {
    gold += amt;
}

int Character::getGold() const {
    return gold;
}
// Changes the remaining HP of given Character
void Character::changeHP(int amt) {
    hp += amt;
}

// Returns the alive(true) / dead(false) status of given Character
bool Character::isDead() const {
    return (hp <= 0) ? true : false;
}

void Character::defaultAttack(Character &c) {
    int damage = ceil((100 * getAtk())/(100 + c.getDef()));
    c.changeHP(-damage);
}

void Character::halfChanceAttack(Character &c) {
    if (rand() % 2 == 0) defaultAttack(c);
}

Character::~Character() {} 
