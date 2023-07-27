#include "../../src/board/vertex.h"
#include "gtest/gtest.h"

TEST(Vertex, GetVertexNumber) {
    Vertex vertex = Vertex(15);
    EXPECT_EQ(vertex.getVertexNumber(), 15);
}
