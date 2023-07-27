#include "../../src/board/board.h"
#include "gtest/gtest.h"

std::vector<TileInitData> sampleTileInitData = {
    TileInitData(3, BRICK),
    TileInitData(10, ENERGY),
    TileInitData(5, HEAT),
    TileInitData(4, ENERGY),
    TileInitData(7, PARK),
    TileInitData(10, HEAT),
    TileInitData(11, GLASS),
    TileInitData(3, BRICK),
    TileInitData(8, HEAT),
    TileInitData(2, BRICK),
    TileInitData(6, BRICK),
    TileInitData(8, ENERGY),
    TileInitData(12, WIFI),
    TileInitData(5, ENERGY),
    TileInitData(11, WIFI),
    TileInitData(4, GLASS),
    TileInitData(6, WIFI),
    TileInitData(9, WIFI),
    TileInitData(9, GLASS)
};

TEST(Board, InitBoardCorrectQuantities) {
    Board board;
    board.initBoard(sampleTileInitData);

    for(int i = 0; i < 19; i++) { EXPECT_EQ(i, board.getTile(i).getTileNumber()); }
    for(int i = 0; i < 72; i++) { EXPECT_EQ(i, board.getEdge(i).getEdgeNumber()); }
    for(int i = 0; i < 54; i++) { EXPECT_EQ(i, board.getVertex(i).getVertexNumber()); }
}

// TODO: Write tests to verify that tileValues and resources are set correctly
