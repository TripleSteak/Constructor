#include "../../src/common/randomengine.h"
#include "../../src/dice/dice.h"
#include "../../src/dice/fairdice.h"
#include "gtest/gtest.h"

TEST(FairDice, RollDice) {
    FairDice fairDice;
    RandomEngine::setSeed(0);

    EXPECT_EQ(fairDice.rollDice(0), 2);
    EXPECT_EQ(fairDice.rollDice(0), 8);
    EXPECT_EQ(fairDice.rollDice(0), 6);
}
