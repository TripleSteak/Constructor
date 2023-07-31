#include "../../src/board/geesetile.h"
#include "../../src/board/tile.h"
#include "../../src/game/builder.h"
#include "../../src/structures/basement.h"
#include "../../src/structures/house.h"
#include "../../src/structures/tower.h"
#include "gtest/gtest.h"

TEST(GeeseTile, GetGeeseTilePrivateFields) {
    std::unique_ptr<AbstractTile> tile = std::make_unique<Tile>(44, 4, HEAT);
    GeeseTile geeseTile(std::move(tile));

    EXPECT_EQ(geeseTile.getTileNumber(), 44);
    EXPECT_EQ(geeseTile.getTileValue(), 4);
    EXPECT_EQ(geeseTile.getResource(), HEAT);
}

TEST(GeeseTile, HasGeese) {
    std::unique_ptr<AbstractTile> tile = std::make_unique<Tile>(55, 5, WIFI);
    GeeseTile geeseTile(std::move(tile));

    EXPECT_EQ(geeseTile.hasGeese(), true);
}

TEST(GeeseTile, GiveResourcesToBuilders) {
    std::unique_ptr<AbstractTile> tile = std::make_unique<Tile>(22, 4, GLASS);
    GeeseTile geeseTile(std::move(tile));

    Vertex vertex1(44);
    Vertex vertex2(45);
    Vertex vertex3(46);
    Vertex vertex4(47);

    Builder builder1(0, 'B', 0);
    Builder builder2(1, 'R', 0);

    std::shared_ptr<Residence> res1 = std::make_shared<Basement>(builder1, vertex1);
    std::shared_ptr<Residence> res2 = std::make_shared<House>(builder1, vertex2);
    std::shared_ptr<Residence> res3 = std::make_shared<Tower>(builder2, vertex3);

    vertex1.buildResidence(res1);
    vertex2.buildResidence(res2);
    vertex3.buildResidence(res3);

    geeseTile.addNeighbouringVertex(&vertex1);
    geeseTile.addNeighbouringVertex(&vertex2);
    geeseTile.addNeighbouringVertex(&vertex3);
    geeseTile.addNeighbouringVertex(&vertex4);

    geeseTile.giveResourcesToBuilders();

    EXPECT_EQ(builder1.inventory[BRICK], 0);
    EXPECT_EQ(builder2.inventory[BRICK], 0);
}

TEST(GeeseTile, RemoveGeese) {
    std::unique_ptr<AbstractTile> tile = std::make_unique<Tile>(11, 10, GLASS);
    GeeseTile geeseTile(std::move(tile));

    std::unique_ptr<AbstractTile> movedTile = geeseTile.removeGeese();

    EXPECT_EQ(movedTile.get()->getTileNumber(), 11);
    EXPECT_EQ(movedTile.get()->getTileValue(), 10);
    EXPECT_EQ(movedTile.get()->getResource(), GLASS);
}
