#ifndef RACE_H
#define RACE_H
#include "character.h"
#include <string>
class Human;
class Dwarf;
class Elf;
class Orc;
class Halfling;
class Merchant;
class Dragon;
class Enemy; 

class Race: public Character {
    std::string race;
    int maxHP;
    double defaultAtk;
    double defaultDef;
    int chamber;
 public:
    Race(std::string race, int hp, double atk, double def, int gold, int x, int y);
    void changeAtk(double amt);
    void changeDef(double amt);
    double getDefaultAtk() const;
    double getDefaultDef() const;
    void resetStats();
    int getMaxHP() const;
    std::string getRace() const;
    int getChamber();
    void changeChamber(int number);
    void attack(Enemy &E);
    void attack(Dragon &D);
    virtual ~Race();
};

#endif
