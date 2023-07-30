#include "../../src/game/filehandler.h"
#include "../../src/game/game.h"
#include "gtest/gtest.h"

TEST(FileHandler, ReadDefaultFIle) {
    Game game;
    FileHandler fh(game);
    fh.loadFromBoard("board.in");
}
