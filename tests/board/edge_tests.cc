#include "../../src/board/edge.h"
#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/road.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/basement.h"
#include "gtest/gtest.h"

TEST(Edge, GetEdgeNumber) {
    Edge edge(44);
    EXPECT_EQ(edge.getEdgeNumber(), 44);
}

TEST(Edge, GetRoad) {
    Edge edge(42);
    Builder builder(3, 'O', 0);
    std::shared_ptr<Road> road = std::make_shared<Road>(builder, edge);

    edge.buildRoad(road);

    EXPECT_EQ(edge.getRoad(), road);
}

TEST(Edge, GetNeighbouringVertices) {
    Edge edge(52);
    Vertex vertex1(92);
    Vertex vertex2(55);

    edge.addNeighbouringVertex(&vertex1);
    edge.addNeighbouringVertex(&vertex2);

    EXPECT_EQ(edge.getNeighbouringVertices().at(0), &vertex1);
    EXPECT_EQ(edge.getNeighbouringVertices().at(1), &vertex2);
}

TEST(Edge, CannotBuildRoadWhenRoadAlreadyExists) {
    Edge edge(52);
    Builder builder(3, 'O', 0);
    std::shared_ptr<Road> road = std::make_shared<Road>(builder, edge);

    edge.buildRoad(road);

    EXPECT_EQ(edge.canBuildRoad(builder), false);
}

TEST(Edge, CanBuildRoadWithAdjacentResidence) {
    Edge edge(11);
    Vertex vertex(12);
    Builder builder1(2, 'B', 0);
    Builder builder2(3, 'G', 0);

    edge.addNeighbouringVertex(&vertex);

    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder1, vertex);
    vertex.buildResidence(res);

    EXPECT_EQ(edge.canBuildRoad(builder1), true);
    EXPECT_EQ(edge.canBuildRoad(builder2), false);
}

TEST(Edge, CanBuildRoadWithAdjacentRoad) {
    Edge edge1(10);
    Edge edge2(11);
    Vertex vertex(12);
    Builder builder1(2, 'B', 0);
    Builder builder2(3, 'G', 0);

    edge1.addNeighbouringVertex(&vertex);
    edge2.addNeighbouringVertex(&vertex);
    vertex.addNeighbouringEdge(&edge1);
    vertex.addNeighbouringEdge(&edge2);

    std::shared_ptr<Road> road = std::make_shared<Road>(builder1, edge2);
    edge2.buildRoad(road);

    EXPECT_EQ(edge1.canBuildRoad(builder1), true);
    EXPECT_EQ(edge1.canBuildRoad(builder2), false);
}

TEST(Edge, CannotBuildRoadThroughOpponentResidence) {
    Edge edge1(10);
    Edge edge2(11);
    Vertex vertex(12);
    Builder builder1(2, 'B', 0);
    Builder builder2(3, 'G', 0);

    edge1.addNeighbouringVertex(&vertex);
    edge2.addNeighbouringVertex(&vertex);
    vertex.addNeighbouringEdge(&edge1);
    vertex.addNeighbouringEdge(&edge2);

    std::shared_ptr<Road> road = std::make_shared<Road>(builder1, edge2);
    edge2.buildRoad(road);

    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder2, vertex);
    vertex.buildResidence(res);

    EXPECT_EQ(edge1.canBuildRoad(builder1), false);
    EXPECT_EQ(edge1.canBuildRoad(builder2), true);
}
