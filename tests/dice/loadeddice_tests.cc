#include "../../src/dice/dice.h"
#include "../../src/dice/loadeddice.h"
#include "gtest/gtest.h"

TEST(LoadedDice, RollDice) {
    LoadedDice loadedDice;

    EXPECT_EQ(loadedDice.rollDice(2), 2);
    EXPECT_EQ(loadedDice.rollDice(5), 5);
    EXPECT_EQ(loadedDice.rollDice(6), 6);
}
