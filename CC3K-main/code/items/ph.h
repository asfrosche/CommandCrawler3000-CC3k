#ifndef _PH_H_
#define _PH_H_
#include "../strategy.h"

class Race;

struct PH : public Strategy {
  public:
  void usePotion(Race &PC) override;
};

#endif
