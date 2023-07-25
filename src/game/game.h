#ifndef GAME_H
#define GAME_H

#include "../common/forward.h"
#include <vector>

class Game final {
  private:
    Board* board;
    std::vector<Builder*> builders;
    Builder* currentTurn;
    FileHandler* fileHandler;

    void beginTurn(Builder&);
    void buildInitialResidences();
    void discardHalfOfTotalResources(Builder&);
    void nextTurn();

    void printBoard();
    void printBuilderStatuses();
    void printResidences();
    void printHelp();

  public:
    Game();
    ~Game();

    void play();
};

#endif