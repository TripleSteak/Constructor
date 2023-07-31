#include "../../src/dice/dice.h"
#include "../../src/dice/fairdice.h"
#include "gtest/gtest.h"

TEST(FairDice, RollDice) {
    FairDice fairDice(15);

    EXPECT_EQ(fairDice.rollDice(0), 7);
    EXPECT_EQ(fairDice.rollDice(0), 9);
    EXPECT_EQ(fairDice.rollDice(0), 8);
}
