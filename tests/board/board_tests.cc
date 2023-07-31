#include "../../src/board/board.h"
#include "../../src/board/edge.h"
#include "gtest/gtest.h"
#include <fstream>

std::vector<TileInitData> sampleTileInitData = {{3, BRICK}, {10, ENERGY}, {5, HEAT}, {4, ENERGY}, {7, PARK}, {10, HEAT}, {11, GLASS}, {3, BRICK}, {8, HEAT}, {2, BRICK}, {6, BRICK}, {8, ENERGY}, {12, WIFI}, {5, ENERGY}, {11, WIFI}, {4, GLASS}, {6, WIFI}, {9, GLASS}, {9, GLASS}};

TEST(Board, CorrectNumberOfTilesEdgesVertices) {
    Board board(sampleTileInitData);

    for (int i = 0; i < 19; i++) {
        EXPECT_EQ(i, board.getTile(i)->getTileNumber());
    }
    for (int i = 0; i < 72; i++) {
        EXPECT_EQ(i, board.getEdge(i)->getEdgeNumber());
    }
    for (int i = 0; i < 54; i++) {
        EXPECT_EQ(i, board.getVertex(i)->getVertexNumber());
    }
}

TEST(Board, CorrectConstructionWithTileInitData) {
    Board board(sampleTileInitData);
    std::ostringstream out;

    std::ifstream file("expected_outputs/board_1.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    board.printBoard(out);

    EXPECT_EQ(out.str(), expectedPrintOutput);
}

TEST(Board, CorrectConstructionWithTileInitDataAndStructureData) {
    Builder builder1{0, 'Y'};
    Builder builder2{1, 'R'};
    Builder builder3{2, 'B'};
    Builder builder4{3, 'O'};

    std::vector<std::pair<int, char>> builder1Residences = {{22, 'T'}, {27, 'B'}};
    std::vector<std::pair<int, char>> builder2Residences = {{11, 'T'}, {42, 'H'}};
    std::vector<std::pair<int, char>> builder3Residences = {{44, 'B'}, {52, 'T'}};
    std::vector<std::pair<int, char>> builder4Residences = {{3, 'H'}, {7, 'T'}, {19, 'B'}};

    std::vector<int> builder1Roads = {33, 36, 40, 44, 48, 52};
    std::vector<int> builder2Roads = {11, 17, 25, 34, 42, 51};
    std::vector<int> builder3Roads = {64, 67, 69, 47, 55, 63};
    std::vector<int> builder4Roads = {3, 5, 13, 21, 30, 35, 31};

    BuilderStructureData builderData1(builder1Residences, builder1Roads);
    BuilderStructureData builderData2(builder2Residences, builder2Roads);
    BuilderStructureData builderData3(builder3Residences, builder3Roads);
    BuilderStructureData builderData4(builder4Residences, builder4Roads);

    std::vector<std::pair<Builder*, BuilderStructureData>> sampleStructureData = {{&builder1, builderData1}, {&builder2, builderData2}, {&builder3, builderData3}, {&builder4, builderData4}};
    Board board(sampleTileInitData, sampleStructureData);
    std::ostringstream out;

    std::ifstream file("expected_outputs/board_2.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    board.printBoard(out);

    EXPECT_EQ(out.str(), expectedPrintOutput);
}

TEST(Board, CannotBuildWithNoResources) {
    Builder builder1{0, 'Y'};
    Builder builder2{1, 'R'};
    Builder builder3{2, 'B'};
    Builder builder4{3, 'O'};

    std::vector<std::pair<int, char>> builder1Residences = {{22, 'T'}, {27, 'B'}};
    std::vector<std::pair<int, char>> builder2Residences = {{11, 'T'}, {42, 'H'}};
    std::vector<std::pair<int, char>> builder3Residences = {{44, 'B'}, {52, 'T'}};
    std::vector<std::pair<int, char>> builder4Residences = {{3, 'H'}, {7, 'T'}, {19, 'B'}};

    std::vector<int> builder1Roads = {33, 36, 40, 44, 48, 52};
    std::vector<int> builder2Roads = {11, 17, 25, 34, 42, 51};
    std::vector<int> builder3Roads = {64, 67, 69, 47, 55, 63};
    std::vector<int> builder4Roads = {3, 5, 13, 21, 30, 35, 31};

    BuilderStructureData builderData1(builder1Residences, builder1Roads);
    BuilderStructureData builderData2(builder2Residences, builder2Roads);
    BuilderStructureData builderData3(builder3Residences, builder3Roads);
    BuilderStructureData builderData4(builder4Residences, builder4Roads);

    std::vector<std::pair<Builder*, BuilderStructureData>> sampleStructureData = {{&builder1, builderData1}, {&builder2, builderData2}, {&builder3, builderData3}, {&builder4, builderData4}};
    Board board(sampleTileInitData, sampleStructureData);
    std::ostringstream out;

    std::ifstream file("expected_outputs/board_3.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    board.buildRoad(builder1, 28, out);
    board.buildRoad(builder2, 8, out);
    board.buildRoad(builder3, 61, out);
    board.buildRoad(builder4, 6, out);

    board.buildResidence(builder1, 32, out);
    board.buildResidence(builder2, 41, out);
    board.buildResidence(builder3, 48, out);
    board.buildResidence(builder4, 20, out);

    board.upgradeResidence(builder1, 27, out);
    board.upgradeResidence(builder2, 42, out);
    board.upgradeResidence(builder3, 44, out);
    board.upgradeResidence(builder4, 19, out);

    board.printBoard(out);

    EXPECT_EQ(out.str(), expectedPrintOutput);
}

TEST(Board, CanBuildWithResources) {
    Builder builder1{0, 'Y'};
    Builder builder2{1, 'R'};
    Builder builder3{2, 'B'};
    Builder builder4{3, 'O'};

    builder1.inventory[BRICK] = 1000;
    builder1.inventory[ENERGY] = 1000;
    builder1.inventory[GLASS] = 1000;
    builder1.inventory[HEAT] = 1000;
    builder1.inventory[WIFI] = 1000;

    builder2.inventory[BRICK] = 1000;
    builder2.inventory[ENERGY] = 1000;
    builder2.inventory[GLASS] = 1000;
    builder2.inventory[HEAT] = 1000;
    builder2.inventory[WIFI] = 1000;

    builder3.inventory[BRICK] = 1000;
    builder3.inventory[ENERGY] = 1000;
    builder3.inventory[GLASS] = 1000;
    builder3.inventory[HEAT] = 1000;
    builder3.inventory[WIFI] = 1000;

    builder4.inventory[BRICK] = 1000;
    builder4.inventory[ENERGY] = 1000;
    builder4.inventory[GLASS] = 1000;
    builder4.inventory[HEAT] = 1000;
    builder4.inventory[WIFI] = 1000;

    std::vector<std::pair<int, char>> builder1Residences = {{22, 'T'}, {27, 'B'}};
    std::vector<std::pair<int, char>> builder2Residences = {{11, 'T'}, {42, 'H'}};
    std::vector<std::pair<int, char>> builder3Residences = {{44, 'B'}, {52, 'T'}};
    std::vector<std::pair<int, char>> builder4Residences = {{3, 'H'}, {7, 'T'}, {19, 'B'}};

    std::vector<int> builder1Roads = {33, 36, 40, 44, 48, 52};
    std::vector<int> builder2Roads = {11, 17, 25, 34, 42, 51};
    std::vector<int> builder3Roads = {64, 67, 69, 47, 55, 63};
    std::vector<int> builder4Roads = {3, 5, 13, 21, 30, 35, 31};

    BuilderStructureData builderData1(builder1Residences, builder1Roads);
    BuilderStructureData builderData2(builder2Residences, builder2Roads);
    BuilderStructureData builderData3(builder3Residences, builder3Roads);
    BuilderStructureData builderData4(builder4Residences, builder4Roads);

    std::vector<std::pair<Builder*, BuilderStructureData>> sampleStructureData = {{&builder1, builderData1}, {&builder2, builderData2}, {&builder3, builderData3}, {&builder4, builderData4}};
    Board board(sampleTileInitData, sampleStructureData);
    std::ostringstream out;

    std::ifstream file("expected_outputs/board_4.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    board.buildRoad(builder1, 28, out);
    board.buildRoad(builder2, 8, out);
    board.buildRoad(builder3, 61, out);
    board.buildRoad(builder4, 6, out);

    board.buildResidence(builder1, 32, out);
    board.buildResidence(builder2, 41, out);
    board.buildResidence(builder3, 48, out);
    board.buildResidence(builder4, 20, out);

    board.buildInitialResidence(builder1, 46, out);
    board.buildInitialResidence(builder2, 50, out);
    board.buildInitialResidence(builder3, 30, out);
    board.buildInitialResidence(builder4, 12, out);

    board.upgradeResidence(builder1, 27, out);
    board.upgradeResidence(builder2, 42, out);
    board.upgradeResidence(builder3, 44, out);
    board.upgradeResidence(builder4, 19, out);

    board.printBoard(out);

    EXPECT_EQ(out.str(), expectedPrintOutput);
}

TEST(Board, CannotBuildInInvalidSpots) {
    Builder builder1{0, 'Y'};
    Builder builder2{1, 'R'};
    Builder builder3{2, 'B'};
    Builder builder4{3, 'O'};

    std::vector<std::pair<int, char>> builder1Residences = {{22, 'T'}, {27, 'B'}};
    std::vector<std::pair<int, char>> builder2Residences = {{11, 'T'}, {42, 'H'}};
    std::vector<std::pair<int, char>> builder3Residences = {{44, 'B'}, {52, 'T'}};
    std::vector<std::pair<int, char>> builder4Residences = {{3, 'H'}, {7, 'T'}, {19, 'B'}};

    std::vector<int> builder1Roads = {33, 36, 40, 44, 48, 52};
    std::vector<int> builder2Roads = {11, 17, 25, 34, 42, 51};
    std::vector<int> builder3Roads = {64, 67, 69, 47, 55, 63};
    std::vector<int> builder4Roads = {3, 5, 13, 21, 30, 35, 31};

    BuilderStructureData builderData1(builder1Residences, builder1Roads);
    BuilderStructureData builderData2(builder2Residences, builder2Roads);
    BuilderStructureData builderData3(builder3Residences, builder3Roads);
    BuilderStructureData builderData4(builder4Residences, builder4Roads);

    std::vector<std::pair<Builder*, BuilderStructureData>> sampleStructureData = {{&builder1, builderData1}, {&builder2, builderData2}, {&builder3, builderData3}, {&builder4, builderData4}};
    Board board(sampleTileInitData, sampleStructureData);
    std::ostringstream out;

    std::ifstream file("expected_outputs/board_5.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    board.buildRoad(builder1, 3, out);
    board.buildRoad(builder2, 0, out);
    board.buildRoad(builder3, 1, out);
    board.buildRoad(builder4, 2, out);

    board.buildResidence(builder1, 22, out);
    board.buildResidence(builder2, 23, out);
    board.buildResidence(builder3, 22, out);
    board.buildResidence(builder4, 23, out);

    board.buildInitialResidence(builder1, 42, out);
    board.buildInitialResidence(builder2, 36, out);
    board.buildInitialResidence(builder3, 42, out);
    board.buildInitialResidence(builder4, 36, out);

    board.upgradeResidence(builder1, 0, out);
    board.upgradeResidence(builder2, 1, out);
    board.upgradeResidence(builder3, 0, out);
    board.upgradeResidence(builder4, 1, out);

    board.printBoard(out);

    EXPECT_EQ(out.str(), expectedPrintOutput);
}

TEST(Board, SetGetGeeseTile) {
    Board board(sampleTileInitData);

    EXPECT_EQ(board.getGeeseTile(), 4);
    EXPECT_EQ(board.getTile(4)->hasGeese(), true);

    board.setGeeseTile(15);

    EXPECT_EQ(board.getGeeseTile(), 15);
    EXPECT_EQ(board.getTile(4)->hasGeese(), false);
    EXPECT_EQ(board.getTile(15)->hasGeese(), true);
}
