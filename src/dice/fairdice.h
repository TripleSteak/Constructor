#ifndef FAIRDICE_H
#define FAIRDICE_H

#include "../common/forward.h"
#include "dice.h"

class FairDice final : public Dice {
  private:
    unsigned seed;
  public:
    FairDice(unsigned);
    ~FairDice();

    int rollDice(int) const override;
};

#endif
