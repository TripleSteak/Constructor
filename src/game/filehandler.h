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

    Game* loadFromGame(std::string);
    Game* loadFromBoard(std::string);
    void save(const Game&, std::string);
};

#endif
