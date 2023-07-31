#ifndef GAME_H
#define GAME_H

#include "../board/board.h"
#include "../common/forward.h"
#include "../common/resource.h"
#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <vector>

// Stores information used to builders
struct BuilderResourceData {
    int brickNum;
    int energyNum;
    int glassNum;
    int heatNum;
    int wifiNum;
    int parkNum;  
};

struct BuilderStructureData{
  std::vector<std::pair<int, char>> residences;  
  std::vector<int> roads; 
};


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
    std::vector<const Builder*> getBuilders() const;
    int getGooseLocation() const;
    const Board& getBoard() const;

    void play();
};

#endif
