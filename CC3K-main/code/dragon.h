#ifndef DRAGON_H
#define DRAGON_H
#include "character.h"
#include <string>
class Race;

class Dragon: public Character {
    std::pair<int, int> hoardLocation;
 public:
    Dragon(std::pair<int, int> hoardLocation, int x, int y);
    std::string checkPC();
    void attack(Race &PC);
    void setHoardLoc(std::pair<int, int> loc);
    std::pair<int, int> getHoardLoc();
    ~Dragon();
};

#endif

