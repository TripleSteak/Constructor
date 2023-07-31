#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/tower.h"
#include "../../src/structures/road.h"
#include "gtest/gtest.h"

TEST(Vertex, GetVertexNumber) {
    Vertex vertex(15);

    EXPECT_EQ(vertex.getVertexNumber(), 15);
}

TEST(Vertex, GetResidence) {
    Vertex vertex(16);
    Builder builder(2, 'B', 0);
    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder, vertex);

    vertex.buildResidence(res);

    EXPECT_EQ(vertex.getResidence(), res);
}

TEST(Vertex, GetNeighbouringEdges) {
    Vertex vertex(11);
    Edge edge1(1);
    Edge edge2(2);

    vertex.addNeighbouringEdge(&edge1);
    vertex.addNeighbouringEdge(&edge2);

    EXPECT_EQ(vertex.getNeighbouringEdges().at(0), &edge1);
    EXPECT_EQ(vertex.getNeighbouringEdges().at(1), &edge2);
}

TEST(Vertex, CannotBuildResidenceIfAlreadyExists) {
    Vertex vertex(16);
    Builder builder(2, 'B', 0);

    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder, vertex);
    vertex.buildResidence(res);

    EXPECT_EQ(vertex.canBuildResidence(builder), false);
    EXPECT_EQ(vertex.canBuildInitialResidence(), false);
}

TEST(Vertex, CannotBuildResidenceTooCloseToAnotherResidence) {
    Vertex vertex1(4);
    Vertex vertex2(5);
    Edge edge(12);
    Builder builder(3, 'G', 0);

    vertex1.addNeighbouringEdge(&edge);
    vertex2.addNeighbouringEdge(&edge);
    edge.addNeighbouringVertex(&vertex1);
    edge.addNeighbouringVertex(&vertex2);

    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder, vertex2);
    vertex2.buildResidence(res);

    EXPECT_EQ(vertex1.canBuildResidence(builder), false);
    EXPECT_EQ(vertex1.canBuildInitialResidence(), false);
}

TEST(Vertex, CannotBuildResidenceWithoutRoad) {
    Vertex vertex(2);
    Edge edge(5);
    Builder builder(0, 'Y', 0);

    vertex.addNeighbouringEdge(&edge);
    edge.addNeighbouringVertex(&vertex);

    EXPECT_EQ(vertex.canBuildResidence(builder), false);
    EXPECT_EQ(vertex.canBuildInitialResidence(), true);
}

TEST(Vertex, CanBuildResidenceWithRoad) {
    Vertex vertex(2);
    Edge edge(5);
    Builder builder1(0, 'Y', 0);
    Builder builder2(1, 'G', 0);

    vertex.addNeighbouringEdge(&edge);
    edge.addNeighbouringVertex(&vertex);

    std::shared_ptr<Road> road = std::make_shared<Road>(builder1, edge);
    edge.buildRoad(road);

    EXPECT_EQ(vertex.canBuildResidence(builder1), true);
    EXPECT_EQ(vertex.canBuildResidence(builder2), false);
}

TEST(Vertex, CannotUpgradeResidenceThatDoesntExist) {
    Vertex vertex(5);
    Builder builder(0, 'Y', 0);

    EXPECT_EQ(vertex.canUpgradeResidence(builder), false);
}

TEST(Vertex, CannotUpgradeResidenceThatIsTower) {
    Vertex vertex(5);
    Builder builder(0, 'Y', 0);

    std::shared_ptr<Residence> res = std::make_shared<Tower>(builder, vertex);
    vertex.buildResidence(res);

    EXPECT_EQ(vertex.canUpgradeResidence(builder), false);
}

TEST(Vertex, CanUpgradeResidence) {
    Vertex vertex(5);
    Builder builder1(0, 'Y', 0);
    Builder builder2(1, 'G', 0);

    std::shared_ptr<Residence> res = std::make_shared<Basement>(builder1, vertex);
    vertex.buildResidence(res);

    EXPECT_EQ(vertex.canUpgradeResidence(builder1), true);
    EXPECT_EQ(vertex.canUpgradeResidence(builder2), false);
}
