#ifndef _WD_H_
#define _WD_H_
#include "../strategy.h"

class Race;

struct WD : public Strategy {
  void usePotion(Race &PC) override;
};

#endif
