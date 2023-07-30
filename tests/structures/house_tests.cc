#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/house.h"
#include "gtest/gtest.h"

TEST(House, GetOwner) {
    Builder builder(4, 'B');
    Vertex location = Vertex(14);
    House house(builder, location);

    EXPECT_EQ(house.getOwner(), builder);
}

TEST(House, GetLocation) {
    Builder builder(3, 'C');
    Vertex location = Vertex(15);
    House house(builder, location);

    EXPECT_EQ(house.getLocation(), location);
}

TEST(House, GetBuildingPoints) {
    Builder builder(2, 'D');
    Vertex location(16);
    House house(builder, location);
    EXPECT_EQ(house.getBuildingPoints(), 2);
}

TEST(House, GetResidenceLetter) {
    Builder builder(1, 'A');
    Vertex location(17);
    House house(builder, location);
    EXPECT_EQ(house.getResidenceLetter(), 'H');
}

TEST(House, GetResourceMultiplier) {
    Builder builder(2, 'B');
    Vertex location(18);
    House house(builder, location);
    EXPECT_EQ(house.getResourceMultiplier(), 2);
}
