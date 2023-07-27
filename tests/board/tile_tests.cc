#include "../../src/board/tile.h"
#include "gtest/gtest.h"

TEST(Tile, GetTilePrivateFields) {
    Tile tile = Tile(33, 3, GLASS);
    EXPECT_EQ(tile.getTileNumber(), 33);
    EXPECT_EQ(tile.getTileValue(), 3);
    EXPECT_EQ(tile.getResource(), GLASS);
}
