#include "../../src/dice/dice.h"
#include "../../src/dice/loadeddice.h"
#include "../../src/game/builder.h"
#include "gtest/gtest.h"

TEST(LoadedDice, RollDice) {
    LoadedDice loadedDice;

    EXPECT_EQ(loadedDice.rollDice(2), 2);
    EXPECT_EQ(loadedDice.rollDice(5), 5);
    EXPECT_EQ(loadedDice.rollDice(6), 6);
}

TEST(LoadedDice, RollDiceWithBuilder) {
    Builder builder(1, 'B');
    int roll = builder.rollDice(1);

    EXPECT_EQ(roll, 1);
}
