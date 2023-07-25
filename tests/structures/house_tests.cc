#include "gtest/gtest.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/house.h"

TEST(House, GetOwner) {
    int owner = 2;
    House house = House(owner, nullptr);
    EXPECT_EQ(house.getOwner(), owner);
}

// TODO:
// TEST(House, GetLocation) {}

TEST(House, GetBuildingPoints) {
    House house = House(0, nullptr);
    EXPECT_EQ(house.getBuildingPoints(), 2);
}

TEST(House, GetResidenceLetter) {
    House house = House(0, nullptr);
    EXPECT_EQ(house.getResidenceLetter(), 'H');
}

TEST(House, GetResourceMultiplier) {
    House house = House(0, nullptr);
    EXPECT_EQ(house.getResourceMultiplier(), 2);
}
