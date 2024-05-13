#ifndef _RH_H_
#define _RH_H_
#include "../strategy.h"

class Race;

struct RH : public Strategy {
  public:
  void usePotion(Race &PC) override;
};

#endif
