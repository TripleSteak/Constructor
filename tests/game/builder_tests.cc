#include "../../src/board/edge.h"
#include "../../src/game/builder.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/house.h"
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

TEST(Builder, GetBuilderColourAsString) {
    Builder builder1(0, 'B');
    Builder builder2(1, 'R');
    Builder builder3(2, 'O');
    Builder builder4(3, 'Y');

    EXPECT_EQ(builder1.getBuilderColourString(), "Blue");
    EXPECT_EQ(builder2.getBuilderColourString(), "Red");
    EXPECT_EQ(builder3.getBuilderColourString(), "Orange");
    EXPECT_EQ(builder4.getBuilderColourString(), "Yellow");
}

TEST(Builder, GetBuildingPointsEmpty) {
    Builder builder(3, 'G');
    EXPECT_EQ(builder.getBuildingPoints(), 0);
}

TEST(Builder, GetBuildingPointsNonEmpty) {
    Builder builder(2, 'Y');

    Vertex location1(24);
    Vertex location2(32);
    Vertex location3(48);
    std::shared_ptr<Basement> res1 = std::make_shared<Basement>(builder, location1);
    std::shared_ptr<House> res2 = std::make_shared<House>(builder, location2);
    std::shared_ptr<Tower> res3 = std::make_shared<Tower>(builder, location3);

    builder.residences.push_back(res1);
    EXPECT_EQ(builder.getBuildingPoints(), 1);

    builder.residences.push_back(res2);
    EXPECT_EQ(builder.getBuildingPoints(), 3);

    builder.residences.push_back(res3);
    EXPECT_EQ(builder.getBuildingPoints(), 6);
}

TEST(Builder, GetTotalResourceQuantity) {
    Builder builder(3, 'Y');

    EXPECT_EQ(builder.getTotalResourceQuantity(), 0);

    builder.inventory[BRICK] = 4;
    builder.inventory[GLASS] = 7;
    builder.inventory[WIFI] = 3;

    EXPECT_EQ(builder.getTotalResourceQuantity(), 14);
}

TEST(Builder, GetStatus) {
    Builder builder(3, 'Y');

    Vertex location(13);
    std::shared_ptr<House> house = std::make_shared<House>(builder, location);
    builder.residences.push_back(house);

    builder.inventory.at(BRICK) = 2;
    builder.inventory.at(ENERGY) = 5;
    builder.inventory.at(GLASS) = 1;
    builder.inventory.at(HEAT) = 0;
    builder.inventory.at(WIFI) = 4;

    EXPECT_EQ(builder.getStatus(), "Yellow has 2 building points, 2 brick, 5 energy, 1 glass, 0 heat, and 4 WiFi.");
}

TEST(Builder, GetHasLoadedDice) {
    Builder builder(3, 'Y');
    EXPECT_EQ(builder.getHasLoadedDice(), true);

    builder.setDice(false);
    EXPECT_EQ(builder.getHasLoadedDice(), false);

    builder.setDice(true);
    EXPECT_EQ(builder.getHasLoadedDice(), true);
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
    std::ostringstream out;

    Trade trade = builder.proposeTrade("RED", "BRICK", "ENERGY", out);
    EXPECT_EQ(trade.proposeeColour, "Red");
    EXPECT_EQ(trade.resourceToGive, BRICK);
    EXPECT_EQ(trade.resourceToTake, ENERGY);
    EXPECT_EQ(out.str(), "Yellow offers Red one BRICK for one ENERGY.\n");
}

TEST(Builder, RespondToTradeWithNo) {
    Builder builder(0, 'R');
    std::istringstream in("no");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does Red accept this offer?\n");
    EXPECT_EQ(tradeResponse, false);
}

TEST(Builder, RespondToTradeWithYes) {
    Builder builder(0, 'B');
    std::istringstream in("yes");
    std::ostringstream out;

    bool tradeResponse = builder.respondToTrade(in, out);
    EXPECT_EQ(out.str(), "Does Blue accept this offer?\n");
    EXPECT_EQ(tradeResponse, true);
}

TEST(Builder, TryBuildRoadWithInsufficientResources) {
    Builder builder(2, 'Y');
    Edge edge(27);
    std::shared_ptr<Road> road = builder.tryBuildRoad(edge);
    
    EXPECT_EQ(road, nullptr);
}


TEST(Builder, TryBuildRoadWithSufficientResources) {
    Builder builder(2, 'G');
    builder.inventory[HEAT] = 3;
    builder.inventory[WIFI] = 4;

    Edge edge(27);
    std::shared_ptr<Road> road = builder.tryBuildRoad(edge);

    EXPECT_NE(road, nullptr);
    EXPECT_EQ(builder.inventory[HEAT], 2);
    EXPECT_EQ(builder.inventory[WIFI], 3);
}

TEST(Builder, TryBuildResidenceWithInsufficientResources) {
    Builder builder(3, 'Y');
    Vertex vertex(46);
    std::shared_ptr<Residence> residence = builder.tryBuildResidence(vertex);

    EXPECT_EQ(residence, nullptr);
}

TEST(Builder, TryBuildResidenceWithSufficientResources) {
    Builder builder(3, 'Y');
    builder.inventory[BRICK] = 2;
    builder.inventory[ENERGY] = 3;
    builder.inventory[GLASS] = 4;
    builder.inventory[WIFI] = 5;

    Vertex vertex(46);
    std::shared_ptr<Residence> residence = builder.tryBuildResidence(vertex);

    EXPECT_NE(residence, nullptr);
    EXPECT_EQ(residence.get()->getResidenceLetter(), 'B');

    EXPECT_EQ(builder.inventory[BRICK], 1);
    EXPECT_EQ(builder.inventory[ENERGY], 2);
    EXPECT_EQ(builder.inventory[GLASS], 3);
    EXPECT_EQ(builder.inventory[WIFI], 4);
}

TEST(Builder, TryBuildInitialResidence) {
    Builder builder(2, 'G');
    Vertex vertex(33);
    std::shared_ptr<Residence> residence = builder.tryBuildInitialResidence(vertex);

    EXPECT_NE(residence, nullptr);
    EXPECT_EQ(residence.get()->getResidenceLetter(), 'B');
}

TEST(Builder, TryUpgradeToHouseWithInsufficientResources) {
    Builder builder(1, 'B');
    Vertex vertex(34);
    vertex.buildResidence(builder.tryBuildInitialResidence(vertex));
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(vertex);

    EXPECT_EQ(residence, nullptr);
}

TEST(Builder, TryUpgradeToHouseWithSufficientResources) {
    Builder builder(1, 'B');
    builder.inventory[GLASS] = 8;
    builder.inventory[HEAT] = 8;

    Vertex vertex(34);
    vertex.buildResidence(builder.tryBuildInitialResidence(vertex));
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(vertex);

    EXPECT_NE(residence, nullptr);
    EXPECT_EQ(residence.get()->getResidenceLetter(), 'H');

    EXPECT_EQ(builder.inventory[GLASS], 6);
    EXPECT_EQ(builder.inventory[HEAT], 5);
}

TEST(Builder, TryUpgradeToTowerWithInsufficientResources) {
    Builder builder(1, 'B');
    builder.inventory[GLASS] = 2;
    builder.inventory[HEAT] = 3;

    Vertex vertex(34);
    vertex.buildResidence(builder.tryBuildInitialResidence(vertex));
    vertex.buildResidence(builder.tryUpgradeResidence(vertex));
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(vertex);

    EXPECT_EQ(residence, nullptr);
}

TEST(Builder, TryUpgradeToTowerWithSufficientResources) {
    Builder builder(1, 'B');
    builder.inventory[BRICK] = 18;
    builder.inventory[ENERGY] = 18;
    builder.inventory[GLASS] = 18;
    builder.inventory[HEAT] = 18;
    builder.inventory[WIFI] = 18;

    Vertex vertex(34);
    vertex.buildResidence(builder.tryBuildInitialResidence(vertex));
    vertex.buildResidence(builder.tryUpgradeResidence(vertex));
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(vertex);

    EXPECT_NE(residence, nullptr);
    EXPECT_EQ(residence.get()->getResidenceLetter(), 'T');

    EXPECT_EQ(builder.inventory[BRICK], 15);
    EXPECT_EQ(builder.inventory[ENERGY], 16);
    EXPECT_EQ(builder.inventory[GLASS], 14);
    EXPECT_EQ(builder.inventory[HEAT], 13);
    EXPECT_EQ(builder.inventory[WIFI], 17);
}

TEST(Builder, TryUpgradePastTowerReturnsNullptr) {
    Builder builder(1, 'B');
    builder.inventory[BRICK] = 18;
    builder.inventory[ENERGY] = 18;
    builder.inventory[GLASS] = 18;
    builder.inventory[HEAT] = 18;
    builder.inventory[WIFI] = 18;

    Vertex vertex(34);
    builder.tryBuildInitialResidence(vertex);
    builder.tryUpgradeResidence(vertex);
    builder.tryUpgradeResidence(vertex);
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(vertex);

    EXPECT_EQ(residence, nullptr);
}
