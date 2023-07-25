#include "../../src/game/builder.h"
#include "../../src/structures/residence.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/house.h"
#include "../../src/structures/tower.h"
#include "../../src/board/vertex.h"
#include "gtest/gtest.h"

TEST(Builder, GetBuilderNumber) {
    int builderNumber = 3;
    Builder builder = Builder(builderNumber, 'G');
    EXPECT_EQ(builder.getBuilderNumber(), builderNumber);
}

TEST(Builder, GetBuilderColour) {
    char builderColour = 'B';
    Builder builder = Builder(2, builderColour);
    EXPECT_EQ(builder.getBuilderColour(), builderColour);
}

TEST(Builder, GetBuildingPointsEmpty) {
    Builder builder = Builder(3, 'G');
    EXPECT_EQ(builder.getBuildingPoints(), 0);
}

TEST(Builder, GetBuildingPointsNonEmpty) {
    Builder builder = Builder(2, 'Y');

    Vertex location1 = Vertex(24);
    Vertex location2 = Vertex(32);
    Vertex location3 = Vertex(48);
    Basement res1 = Basement(2, location1);
    House res2 = House(2, location2);
    Tower res3 = Tower(2, location3);

    builder.residences.push_back(&res1);
    EXPECT_EQ(builder.getBuildingPoints(), 1);

    builder.residences.push_back(&res2);
    EXPECT_EQ(builder.getBuildingPoints(), 3);

    builder.residences.push_back(&res3);
    EXPECT_EQ(builder.getBuildingPoints(), 6);
}

TEST(Builder, GetStatus) {
    Builder builder = Builder(3, 'G');

    Vertex location = Vertex(13);
    House house = House(3, location);
    builder.residences.push_back(&house);

    builder.inventory.at(BRICK) = 2;
    builder.inventory.at(ENERGY) = 5;
    builder.inventory.at(GLASS) = 1;
    builder.inventory.at(HEAT) = 0;
    builder.inventory.at(WIFI) = 4;

    EXPECT_EQ(builder.getStatus(), "G has 2 building points, 2 brick, 5 energy, 1 glass, 0 heat, and 4 WiFi.");
}

TEST(Builder, ChooseGeeseSpot) {
    Builder builder = Builder(3, 'Y');
    std::istringstream in("14");
    std::ostringstream out;

    int geeseSpot = builder.chooseGeeseSpot(in, out);
    EXPECT_EQ(out.str(), "Choose where to place the GEESE.\n");
    EXPECT_EQ(geeseSpot, 14);
}

TEST(Builder, Steal) {
    Builder builder = Builder(2, 'G');
    std::istringstream in("B");
    std::ostringstream out;

    char stealFrom = builder.steal(in, out);
    EXPECT_EQ(out.str(), "Choose a builder to steal from.\n");
    EXPECT_EQ(stealFrom, 'B');
}

TEST(Builder, ProposeTrade) {
    Builder builder = Builder(1, 'Y');
    std::istringstream in("R BRICK ENERGY");
    std::ostringstream out;

    Trade trade = builder.proposeTrade(in, out);
    EXPECT_EQ(trade.proposeeColour, 'R');
    EXPECT_EQ(trade.resourceToGive, BRICK);
    EXPECT_EQ(trade.resourceToTake, ENERGY);
}

TEST(Builder, RespondToTradeWithNo) {
    Builder builder = Builder(0, 'R');
    std::istringstream in("no");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does R accept this offer?\n");
    EXPECT_EQ(tradeResponse, false);
}

TEST(Builder, RespondToTradeWithYes) {
    Builder builder = Builder(0, 'B');
    std::istringstream in("yes");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does B accept this offer?\n");
    EXPECT_EQ(tradeResponse, true);
}
