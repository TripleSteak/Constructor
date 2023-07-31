#include "../../src/game/game.h"
#include "../../src/game/gamefactory.h"
#include "gtest/gtest.h"

TEST(GameFactory, ReadDefaultFIle) {
    Game game;
    GameFactory fh(0);
    fh.loadFromBoard("board.in");
}

TEST(GameFactory, SaveGame) {
    // TODO
}
