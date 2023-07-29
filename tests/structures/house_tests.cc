#include "../../src/board/vertex.h"
#include "../../src/structures/house.h"
#include "gtest/gtest.h"

TEST(House, GetOwner) {
    Vertex location = Vertex(14);
    House house = House(2, location);

    EXPECT_EQ(house.getOwner(), 2);
}

TEST(House, GetLocation) {
    Vertex location = Vertex(15);
    House house = House(1, location);

    EXPECT_EQ(house.getLocation(), location);
}

TEST(House, GetBuildingPoints) {
    Vertex location = Vertex(16);
    House house = House(3, location);
    EXPECT_EQ(house.getBuildingPoints(), 2);
}

TEST(House, GetResidenceLetter) {
    Vertex location = Vertex(17);
    House house = House(2, location);
    EXPECT_EQ(house.getResidenceLetter(), 'H');
}

TEST(House, GetResourceMultiplier) {
    Vertex location = Vertex(18);
    House house = House(1, location);
    EXPECT_EQ(house.getResourceMultiplier(), 2);
}
