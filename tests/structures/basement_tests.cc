#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/basement.h"
#include "gtest/gtest.h"

TEST(Basement, GetOwner) {
    Builder builder(1, 'A');
    Vertex location(14);
    Basement basement(builder, location);

    EXPECT_EQ(basement.getOwner(), builder);
}

TEST(Basement, GetLocation) {
    Builder builder(2, 'B');
    Vertex location(15);
    Basement basement(builder, location);

    EXPECT_EQ(basement.getLocation(), location);
}

TEST(Basement, GetBuildingPoints) {
    Builder builder(3, 'C');
    Vertex location(16);
    Basement basement(builder, location);
    EXPECT_EQ(basement.getBuildingPoints(), 1);
}

TEST(Basement, GetResidenceLetter) {
    Builder builder(3, 'C');
    Vertex location(17);
    Basement basement(builder, location);
    EXPECT_EQ(basement.getResidenceLetter(), 'B');
}

TEST(Basement, GetResourceMultiplier) {
    Builder builder(3, 'C');
    Vertex location(18);
    Basement basement(builder, location);
    EXPECT_EQ(basement.getResourceMultiplier(), 1);
}
