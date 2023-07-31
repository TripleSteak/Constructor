#ifndef FAIRDICE_H
#define FAIRDICE_H

#include "../common/forward.h"
#include "dice.h"
#include <random>

class FairDice final : public Dice {
  private:
    std::uniform_int_distribution<int> distribution;

  public:
    FairDice();
    ~FairDice();

    int rollDice(int) override;
};

#endif
