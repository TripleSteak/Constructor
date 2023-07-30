#include "fairdice.h"
#include <cstdlib>
#include <time.h>
#include <memory>
#include <random>
#include <algorithm>
#include <vector>

FairDice::FairDice(unsigned seed) : Dice(), seed{seed} {}
FairDice::~FairDice() {}

int FairDice::rollDice(int roll) const {
    // set seed for random number generator
    std::vector<int> diceRolls = {1, 2, 3, 4, 5, 6};
    std::default_random_engine rng{seed};
    std::shuffle (diceRolls.begin(), diceRolls.end(), rng);
    int rollOne = diceRolls[0];
    std::shuffle (diceRolls.begin(), diceRolls.end(), rng);
    int rollTwo = diceRolls[0];
    return rollOne + rollTwo;
}
