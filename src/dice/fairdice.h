#ifndef FAIRDICE_H
#define FAIRDICE_H

#include "../common/forward.h"
#include "dice.h"
#include <random>

class FairDice final : public Dice {
  private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;

  public:
    FairDice(unsigned);
    ~FairDice();

    int rollDice(int) override;
};

#endif
