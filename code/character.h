#ifndef CHARACTER_H
#define CHARACTER_H
#include "piece.h"

class Character: public Piece {
    int hp;
    int gold;
  protected:
    double atk;
    double def;
  public:
    Character(int hp, double atk, double def, int gold, char type, int x, int y);
    int getHP() const;
    double getAtk() const;
    double getDef() const;
    int getGold() const;
    void addGold(int amt);
    void changeHP(int amt);
    bool isDead() const; 
    virtual void defaultAttack(Character &c);
    virtual void halfChanceAttack(Character &c);
    ~Character();
};

#endif
