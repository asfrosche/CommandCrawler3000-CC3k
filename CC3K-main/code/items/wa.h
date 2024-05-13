#ifndef _WA_H_
#define _WA_H_
#include "../strategy.h"

class Race;

struct WA : public Strategy {
  void usePotion(Race &PC) override;
};

#endif
