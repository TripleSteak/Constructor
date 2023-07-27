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

    void beginTurn(const Builder&);
    void buildInitialResidences();
    void discardHalfOfTotalResources(const Builder&); // Invoked when a 7 is rolled and Builders' hands are too large
    void nextTurn();

    void printBoard() const;
    void printBuilderStatuses() const;
    void printResidences() const;
    void printHelp() const;

  public:
    Game();
    ~Game();

    void play();
};

#endif
