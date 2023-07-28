#ifndef GAME_H
#define GAME_H

#include "../common/forward.h"
#include <memory>
#include <vector>

class Game final {
  private:
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Builder>> builders;
    int currentBuilder; // Index of current builder in builders
    std::unique_ptr<FileHandler> fileHandler;

    void beginTurn(const Builder&);
    void buildInitialResidences();
    void discardHalfOfTotalResources(); // Invoked when a 7 is rolled and
                                        // Builders' hands are too large
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
