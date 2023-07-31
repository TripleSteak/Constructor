#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/house.h"
#include "gtest/gtest.h"

TEST(House, GetOwner) {
    Builder builder(4, 'B', 0);
    Vertex location(14);
    House house(builder, location);

    EXPECT_EQ(house.getOwner(), builder);
}

TEST(House, GetLocation) {
    Builder builder(3, 'C', 0);
    Vertex location(15);
    House house(builder, location);

    EXPECT_EQ(house.getLocation(), location);
}

TEST(House, GetBuildingPoints) {
    Builder builder(2, 'D', 0);
    Vertex location(16);
    House house(builder, location);
    EXPECT_EQ(house.getBuildingPoints(), 2);
}

TEST(House, GetResidenceLetter) {
    Builder builder(1, 'A', 0);
    Vertex location(17);
    House house(builder, location);
    EXPECT_EQ(house.getResidenceLetter(), 'H');
}

TEST(House, GetResourceMultiplier) {
    Builder builder(2, 'B', 0);
    Vertex location(18);
    House house(builder, location);
    EXPECT_EQ(house.getResourceMultiplier(), 2);
}
