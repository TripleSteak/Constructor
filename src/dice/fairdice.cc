#include "fairdice.h"

FairDice::FairDice(unsigned seed) : Dice(), engine(seed), distribution(1, 6) {}
FairDice::~FairDice() {}

int FairDice::rollDice(int roll) {
    int rollOne = distribution(engine);
    int rollTwo = distribution(engine);

    return rollOne + rollTwo;
}
