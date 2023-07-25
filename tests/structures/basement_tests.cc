#include "gtest/gtest.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/basement.h"

TEST(Basement, GetOwner) {
    int owner = 2;
    Basement basement = Basement(owner, nullptr);
    EXPECT_EQ(basement.getOwner(), owner);
}

// TODO:
// TEST(Basement, GetLocation) {}

TEST(Basement, GetBuildingPoints) {
    Basement basement = Basement(0, nullptr);
    EXPECT_EQ(basement.getBuildingPoints(), 1);
}

TEST(Basement, GetResidenceLetter) {
    Basement basement = Basement(0, nullptr);
    EXPECT_EQ(basement.getResidenceLetter(), 'B');
}

TEST(Basement, GetResourceMultiplier) {
    Basement basement = Basement(0, nullptr);
    EXPECT_EQ(basement.getResourceMultiplier(), 1);
}
