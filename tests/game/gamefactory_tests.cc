#include "../../src/game/game.h"
#include "../../src/game/gamefactory.h"
#include "gtest/gtest.h"

TEST(GameFactory, ReadDefaultFIle) {
    GameFactory fh(0);
    std::unique_ptr<Game> g = fh.loadFromBoard("board.in");
}

TEST(GameFactory, ReadGameSave) {
    GameFactory fh(0);
    std::unique_ptr<Game> g = fh.loadFromGame("savefile.txt");
}
