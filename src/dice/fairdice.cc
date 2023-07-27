#include "fairdice.h"
#include <time.h>
#include <cstdlib>

FairDice::FairDice() : Dice() {}
FairDice::~FairDice() {}

int FairDice::rollDice(int roll) const {
    //set seed for random number generator
    srand(time(0));
    int rollone = rand() % 6 + 1;
    int rolltwo = rand() % 6 + 1;
    return rollone + rolltwo;
}
