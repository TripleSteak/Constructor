#include "../../src/board/edge.h"
#include "../../src/game/builder.h"
#include "../../src/structures/road.h"
#include "gtest/gtest.h"

TEST(Road, GetOwner) {
    Builder builder(4, 'B');
    Edge location(18);
    Road road(builder, location);

    EXPECT_EQ(road.getOwner().getBuilderNumber(), 4);
}

TEST(Road, GetLocation) {
    Builder builder(33, 'C');
    Edge location(42);
    Road road(builder, location);

    EXPECT_EQ(road.getLocation(), location);
}
