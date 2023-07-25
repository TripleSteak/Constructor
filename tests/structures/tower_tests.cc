#include "../../src/board/vertex.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/tower.h"
#include "gtest/gtest.h"

TEST(Tower, GetOwner) {
    Vertex location = Vertex(14);
    Tower tower = Tower(2, location);

    EXPECT_EQ(tower.getOwner(), 2);
}

TEST(Tower, GetLocation) {
    Vertex location = Vertex(15);
    Tower tower = Tower(1, location);

    EXPECT_EQ(tower.getLocation(), &location);
}

TEST(Tower, GetBuildingPoints) {
    Vertex location = Vertex(16);
    Tower tower = Tower(3, location);
    EXPECT_EQ(tower.getBuildingPoints(), 3);
}

TEST(Tower, GetResidenceLetter) {
    Vertex location = Vertex(17);
    Tower tower = Tower(2, location);
    EXPECT_EQ(tower.getResidenceLetter(), 'T');
}

TEST(Tower, GetResourceMultiplier) {
    Vertex location = Vertex(18);
    Tower tower = Tower(1, location);
    EXPECT_EQ(tower.getResourceMultiplier(), 3);
}
