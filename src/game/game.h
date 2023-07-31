#ifndef GAME_H
#define GAME_H

#include "../board/board.h"
#include "../common/forward.h"
#include "../common/resource.h"
#include "builder.h"
#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <vector>

class Game final {
  private:
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Builder>> builders;
    int currentBuilder; // Index of current builder in builders

    std::vector<TileInitData> generateRandomBoard(unsigned);

    void beginTurn(const Builder&);
    void buildInitialResidences();
    void discardHalfOfTotalResources(); // Invoked when a 7 is rolled and Builders' hands are too large
    void nextTurn();

    void printBoard() const;
    void printBuilderStatuses() const;
    void printResidences() const;
    void printHelp() const;

  public:
    Game(unsigned);
    Game(unsigned, std::vector<TileInitData>);
    Game(unsigned, std::vector<TileInitData>, std::vector<BuilderResourceData>, std::vector<BuilderStructureData>, int currentBuilder, int GeeseTile);
    ~Game();

    int getCurrentBuilder() const;
    const std::vector<const Builder*> getBuilders() const;
    int getGeeseLocation() const;
    const Board& getBoard() const;

    void play();
};

#endif
