#ifndef _BD_H_
#define _BD_H_
#include "../strategy.h"

class Race;

struct BD : public Strategy {
  public:
  void usePotion(Race &PC) override;
};

#endif
