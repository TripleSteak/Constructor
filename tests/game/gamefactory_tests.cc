#include "../../src/game/game.h"
#include "../../src/game/gamefactory.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(GameFactory, LoadFromGame) {
    std::ofstream file("expected_outputs/load_from_game_1.out");
    GameFactory gameFactory(0);
    std::unique_ptr<Game> game = gameFactory.loadFromGame("test_inputs/load_from_game_1.in");

    game.get()->getBoard().printBoard(file);
    file.close();

    EXPECT_EQ(game.get()->getCurrentBuilder(), 1);
}
