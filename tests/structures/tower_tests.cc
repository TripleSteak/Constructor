#include "gtest/gtest.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/tower.h"

TEST(Tower, GetOwner) {
    int owner = 2;
    Tower tower = Tower(owner, nullptr);
    EXPECT_EQ(tower.getOwner(), owner);
}

// TODO:
// TEST(Tower, GetLocation) {}

TEST(Tower, GetBuildingPoints) {
    Tower tower = Tower(0, nullptr);
    EXPECT_EQ(tower.getBuildingPoints(), 3);
}

TEST(Tower, GetResidenceLetter) {
    Tower tower = Tower(0, nullptr);
    EXPECT_EQ(tower.getResidenceLetter(), 'T');
}

TEST(Tower, GetResourceMultiplier) {
    Tower tower = Tower(0, nullptr);
    EXPECT_EQ(tower.getResourceMultiplier(), 3);
}
