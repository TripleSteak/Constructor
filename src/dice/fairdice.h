#ifndef FAIRDICE_H
#define FAIRDICE_H

#include "../common/forward.h"
#include "dice.h"

class FairDice final : public Dice {
  public:
    FairDice();
    ~FairDice();

    int rollDice(int) const override;
};

#endif
