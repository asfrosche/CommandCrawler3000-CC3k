#ifndef _BA_H_
#define _BA_H_
#include "../strategy.h"

class Race;

struct BA : public Strategy {
  public:
    void usePotion(Race &PC) override;
};

#endif
