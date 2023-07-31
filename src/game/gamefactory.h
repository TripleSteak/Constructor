#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "../common/forward.h"
#include "game.h"
#include <memory>
#include <string>

class GameFactory final {
  private:
    const unsigned seed;

  public:
    GameFactory(unsigned);
    ~GameFactory();

    std::unique_ptr<Game> loadFromGame(std::string);  // Pre-existing game data, which includes Builder turns, residences, points, etc.
    std::unique_ptr<Game> loadFromBoard(std::string); // Pre-existing board configuration, which only includes resource placement
    std::unique_ptr<Game> loadFromRandomBoard();      // Randomly generated board configuration
};

#endif
