#include "../../src/board/edge.h"
#include "gtest/gtest.h"

TEST(Edge, GetEdgeNumber) {
    Edge edge = Edge(44);
    EXPECT_EQ(edge.getEdgeNumber(), 44);
}
