#include "../../src/board/tile.h"
#include "../../src/common/inventoryupdate.h"
#include "../../src/game/builder.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/house.h"
#include "../../src/structures/tower.h"
#include "gtest/gtest.h"

TEST(Tile, GetTilePrivateFields) {
    Tile tile(33, 3, GLASS);

    EXPECT_EQ(tile.getTileNumber(), 33);
    EXPECT_EQ(tile.getTileValue(), 3);
    EXPECT_EQ(tile.getResource(), GLASS);
}

TEST(Tile, HasGeese) {
    Tile tile(15, 5, ENERGY);

    EXPECT_EQ(tile.hasGeese(), false);
}

TEST(Tile, GiveResourcesToBuilders) {
    Tile tile(22, 4, BRICK);

    Vertex vertex1(44);
    Vertex vertex2(45);
    Vertex vertex3(46);
    Vertex vertex4(47);

    Builder builder1(0, 'B');
    Builder builder2(1, 'R');

    std::shared_ptr<Residence> res1 = std::make_shared<Basement>(builder1, vertex1);
    std::shared_ptr<Residence> res2 = std::make_shared<House>(builder2, vertex2);
    std::shared_ptr<Residence> res3 = std::make_shared<Tower>(builder2, vertex3);

    vertex1.buildResidence(res1);
    vertex2.buildResidence(res2);
    vertex3.buildResidence(res3);

    tile.addNeighbouringVertex(&vertex1);
    tile.addNeighbouringVertex(&vertex2);
    tile.addNeighbouringVertex(&vertex3);
    tile.addNeighbouringVertex(&vertex4);

    tile.giveResourcesToBuilders();

    EXPECT_EQ(builder1.inventory[BRICK], 1);
    EXPECT_EQ(builder2.inventory[BRICK], 5);
}
