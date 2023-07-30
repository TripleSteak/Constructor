#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/tower.h"
#include "gtest/gtest.h"

TEST(Tower, GetOwner) {
    Builder builder(2, 'A');
    Vertex location(14);
    Tower tower(builder, location);

    EXPECT_EQ(tower.getOwner(), builder);
}

TEST(Tower, GetLocation) {
    Builder builder(3, 'B');
    Vertex location(15);
    Tower tower(builder, location);

    EXPECT_EQ(tower.getLocation(), location);
}

TEST(Tower, GetBuildingPoints) {
    Builder builder(4, 'C');
    Vertex location(16);
    Tower tower(builder, location);
    EXPECT_EQ(tower.getBuildingPoints(), 3);
}

TEST(Tower, GetResidenceLetter) {
    Builder builder(1, 'D');
    Vertex location(17);
    Tower tower(builder, location);
    EXPECT_EQ(tower.getResidenceLetter(), 'T');
}

TEST(Tower, GetResourceMultiplier) {
    Builder builder(2, 'A');
    Vertex location(18);
    Tower tower(builder, location);
    EXPECT_EQ(tower.getResourceMultiplier(), 3);
}
