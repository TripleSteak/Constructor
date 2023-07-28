#include "fairdice.h"
#include <cstdlib>
#include <time.h>

FairDice::FairDice() : Dice() {}
FairDice::~FairDice() {}

int FairDice::rollDice(int roll) const {
    // set seed for random number generator
    srand(time(0));
    int rollOne = rand() % 6 + 1;
    int rollTwo = rand() % 6 + 1;
    return rollOne + rollTwo;
}
