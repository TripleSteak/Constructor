#ifndef DICE_H
#define DICE_H

#include "../common/forward.h"

class Dice {
  public:
    Dice();
    virtual ~Dice();

    virtual int rollDice() const = 0;
};

#endif
