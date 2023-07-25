#include "../../src/board/vertex.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/residence.h"
#include "gtest/gtest.h"

TEST(Basement, GetOwner) {
    Vertex location = Vertex(14);
    Basement basement = Basement(2, location);

    EXPECT_EQ(basement.getOwner(), 2);
}

TEST(Basement, GetLocation) {
    Vertex location = Vertex(15);
    Basement basement = Basement(1, location);

    EXPECT_EQ(basement.getLocation(), &location);
}

TEST(Basement, GetBuildingPoints) {
    Vertex location = Vertex(16);
    Basement basement = Basement(3, location);
    EXPECT_EQ(basement.getBuildingPoints(), 1);
}

TEST(Basement, GetResidenceLetter) {
    Vertex location = Vertex(17);
    Basement basement = Basement(2, location);
    EXPECT_EQ(basement.getResidenceLetter(), 'B');
}

TEST(Basement, GetResourceMultiplier) {
    Vertex location = Vertex(18);
    Basement basement = Basement(1, location);
    EXPECT_EQ(basement.getResourceMultiplier(), 1);
}
