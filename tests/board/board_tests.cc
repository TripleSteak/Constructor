#include "../../src/board/board.h"
#include "../../src/board/edge.h"
#include "../../src/board/tile.h"
#include "../../src/board/vertex.h"
#include "gtest/gtest.h"

std::vector<TileInitData> sampleTileInitData = {{3, BRICK}, {10, ENERGY}, {5, HEAT},  {4, ENERGY}, {7, PARK},   {10, HEAT}, {11, GLASS},
                                                {3, BRICK}, {8, HEAT},    {2, BRICK}, {6, BRICK},  {8, ENERGY}, {12, WIFI}, {5, ENERGY},
                                                {11, WIFI}, {4, GLASS},   {6, WIFI},  {9, WIFI},   {9, GLASS}};

TEST(Board, InitBoardCorrectQuantities) {
    Board board;
    board.initBoard(sampleTileInitData);

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

// TODO: Write tests to verify that tileValues and resources are set correctly
