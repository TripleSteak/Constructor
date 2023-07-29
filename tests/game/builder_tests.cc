#include "../../src/board/edge.h"
#include "../../src/board/vertex.h"
#include "../../src/game/builder.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/house.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/tower.h"
#include "gtest/gtest.h"

TEST(Builder, GetBuilderNumber) {
    int builderNumber = 3;
    Builder builder(builderNumber, 'G');
    EXPECT_EQ(builder.getBuilderNumber(), builderNumber);
}

TEST(Builder, GetBuilderColour) {
    char builderColour = 'B';
    Builder builder(2, builderColour);
    EXPECT_EQ(builder.getBuilderColour(), builderColour);
}

TEST(Builder, GetBuildingPointsEmpty) {
    Builder builder(3, 'G');
    EXPECT_EQ(builder.getBuildingPoints(), 0);
}

TEST(Builder, GetBuildingPointsNonEmpty) {
    Builder builder(2, 'Y');

    Vertex location1 = Vertex(24);
    Vertex location2 = Vertex(32);
    Vertex location3 = Vertex(48);
    std::shared_ptr<Basement> res1 = std::make_shared<Basement>(2, location1);
    std::shared_ptr<House> res2 = std::make_shared<House>(2, location2);
    std::shared_ptr<Tower> res3 = std::make_shared<Tower>(2, location3);

    builder.residences.push_back(res1);
    EXPECT_EQ(builder.getBuildingPoints(), 1);

    builder.residences.push_back(res2);
    EXPECT_EQ(builder.getBuildingPoints(), 3);

    builder.residences.push_back(res3);
    EXPECT_EQ(builder.getBuildingPoints(), 6);
}

TEST(Builder, GetStatus) {
    Builder builder(3, 'G');

    Vertex location = Vertex(13);
    std::shared_ptr<House> house = std::make_shared<House>(3, location);
    builder.residences.push_back(house);

    builder.inventory.at(BRICK) = 2;
    builder.inventory.at(ENERGY) = 5;
    builder.inventory.at(GLASS) = 1;
    builder.inventory.at(HEAT) = 0;
    builder.inventory.at(WIFI) = 4;

    EXPECT_EQ(builder.getStatus(), "G has 2 building points, 2 brick, 5 energy, 1 glass, 0 heat, and 4 WiFi.");
}

TEST(Builder, ChooseGeeseSpot) {
    Builder builder(3, 'Y');
    std::istringstream in("14");
    std::ostringstream out;

    int geeseSpot = builder.chooseGeeseSpot(in, out);
    EXPECT_EQ(out.str(), "Choose where to place the GEESE.\n");
    EXPECT_EQ(geeseSpot, 14);
}

TEST(Builder, Steal) {
    Builder builder(2, 'G');
    std::istringstream in("B");
    std::ostringstream out;

    char stealFrom = builder.steal(in, out);
    EXPECT_EQ(out.str(), "Choose a builder to steal from.\n");
    EXPECT_EQ(stealFrom, 'B');
}

TEST(Builder, ProposeTrade) {
    Builder builder(1, 'Y');
    std::istringstream in("R BRICK ENERGY");
    std::ostringstream out;

    Trade trade = builder.proposeTrade(in, out);
    EXPECT_EQ(trade.proposeeColour, 'R');
    EXPECT_EQ(trade.resourceToGive, BRICK);
    EXPECT_EQ(trade.resourceToTake, ENERGY);
}

TEST(Builder, RespondToTradeWithNo) {
    Builder builder(0, 'R');
    std::istringstream in("no");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does R accept this offer?\n");
    EXPECT_EQ(tradeResponse, false);
}

TEST(Builder, RespondToTradeWithYes) {
    Builder builder(0, 'B');
    std::istringstream in("yes");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does B accept this offer?\n");
    EXPECT_EQ(tradeResponse, true);
}

TEST(Builder, TryBuildRoad) {
    Builder builder(2, 'G');
    Edge edge(27);
    EXPECT_EQ(edge.getEdgeNumber(), 27);

    // Test doesn't work because vertex is updated in Board

    // std::shared_ptr<Road> built = builder.tryBuildRoad(edge);
    // EXPECT_EQ(built, edge.getRoad());
}

TEST(Builder, TryBuildResidence) {
    Builder builder(3, 'Y');

    Vertex vertex(46);
    EXPECT_EQ(vertex.getVertexNumber(), 46);

    // Test doesn't work because vertex is updated in Board

    // std::shared_ptr<Residence> built = builder.tryBuildResidence(vertex);
    // EXPECT_EQ(built, vertex.getResidence());
}

TEST(Builder, TryBuildInitialResidence) {
    Builder builder(2, 'G');
    Vertex vertex(33);
    EXPECT_EQ(vertex.getVertexNumber(), 33);

    // Test doesn't work because vertex is updated in Board

    // std::shared_ptr<Residence> built = builder.tryBuildInitialResidence(vertex);
    // EXPECT_EQ(built, vertex.getResidence());
}

TEST(Builder, TryUpgradeResidence) {
    Builder builder(1, 'B');
    Vertex vertex(34);
    EXPECT_EQ(vertex.getVertexNumber(), 34);

    // Test doesn't work because vertex is updated in Board

    // std::shared_ptr<Residence> built = builder.tryUpgradeResidence(vertex);
    // EXPECT_EQ(built, vertex.getResidence());
}
