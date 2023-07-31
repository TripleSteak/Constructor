#include "../../src/game/game.h"
#include "../../src/game/gamefactory.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(GameFactory, LoadFromGame) {
    GameFactory gameFactory;
    std::unique_ptr<Game> game = gameFactory.loadFromGame("test_inputs/load_from_game.in");
    std::ostringstream out;

    std::ifstream file("expected_outputs/load_from_game.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    game.get()->getBoard().printBoard(out);
    file.close();

    EXPECT_EQ(out.str(), expectedPrintOutput);
    EXPECT_EQ(game.get()->getCurrentBuilder(), 1);
}

TEST(GameFactory, LoadFromBoard) {
    GameFactory gameFactory;
    std::unique_ptr<Game> game = gameFactory.loadFromBoard("test_inputs/load_from_board.in");
    std::ostringstream out;

    std::ifstream file("expected_outputs/load_from_board.out");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expectedPrintOutput = buffer.str();

    game.get()->getBoard().printBoard(out);
    file.close();

    EXPECT_EQ(out.str(), expectedPrintOutput);
}
