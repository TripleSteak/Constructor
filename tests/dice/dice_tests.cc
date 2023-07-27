#include "../../src/dice/dice.cc"
#include "../../src/dice/fairdice.cc"
#include "../../src/dice/loadeddice.cc"
#include "gtest/gtest.h"

TEST(Dice, TestLoadedDice) {
    int builderNumber = 3;
    LoadedDice loadedDice = LoadedDice();
    EXPECT_EQ(loadedDice.rollDice(5), 5);
}


