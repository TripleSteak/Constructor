#include "fairdice.h"
#include "../common/randomengine.h"

FairDice::FairDice() : Dice(), distribution(1, 6) {}
FairDice::~FairDice() {}

int FairDice::rollDice(int roll) {
    int rollOne = distribution(RandomEngine::getEngine());
    int rollTwo = distribution(RandomEngine::getEngine());

    return rollOne + rollTwo;
}
