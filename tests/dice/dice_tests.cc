#include "../../src/dice/dice.h"
#include "../../src/dice/fairdice.h"
#include "../../src/dice/loadeddice.h"
#include "gtest/gtest.h"

TEST(dice, TestLoadedDice) {
    LoadedDice loadedDice;
    EXPECT_EQ(loadedDice.rollDice(5), 5);
}
