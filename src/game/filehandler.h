#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../common/forward.h"
#include <string>

class FileHandler final {
  private:
    Game* game;

  public:
    FileHandler();
    ~FileHandler();

    Game* loadFromGame(std::string); // Pre-existing game data, which includes Builder turns, residences, points, etc.
    Game* loadFromBoard(std::string); // Pre-existing board configuration, which only includes resource placement
    void save(const Game&, std::string);
};

#endif
