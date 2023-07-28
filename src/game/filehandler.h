#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../common/forward.h"
#include <string>

class FileHandler final {
  private:
    Game& game;

  public:
    FileHandler(Game&);
    ~FileHandler();

    void loadFromGame(std::string);  // Pre-existing game data, which includes
                                     // Builder turns, residences, points, etc.
    void loadFromBoard(std::string); // Pre-existing board configuration, which
                                     // only includes resource placement
    void save(std::string);
};

#endif
