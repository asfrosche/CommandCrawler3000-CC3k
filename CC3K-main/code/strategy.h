#ifndef STRATEGY_H
#define STRATEGY_H

class Race;

class Strategy {
    public:
    virtual void usePotion(Race &PC) = 0;
    virtual ~Strategy();
};

#endif
