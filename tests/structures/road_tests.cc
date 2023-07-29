#include "../../src/board/edge.h"
#include "../../src/structures/road.h"
#include "gtest/gtest.h"

TEST(Road, GetOwner) {
    Edge location = Edge(18);
    Road road = Road(4, location);

    EXPECT_EQ(road.getOwner(), 4);
}

TEST(Road, GetLocation) {
    Edge location = Edge(42);
    Road road = Road(33, location);

    EXPECT_EQ(road.getLocation(), location);
}
