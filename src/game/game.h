#ifndef GAME_H
#define GAME_H

#include "../board/board.h"
#include "../common/forward.h"
#include "../common/resource.h"
#include "../common/trade.h"
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
    std::default_random_engine rng;

    std::vector<TileInitData> generateRandomBoard(unsigned);

    Builder& getBuilder(std::string);
    void beginTurn(std::istream&, std::ostream&);
    void duringTurn(std::istream&, std::ostream&, int);
    void buildInitialResidences(std::istream&, std::ostream&);
    void moveGeese(std::istream&, std::ostream&);
    std::vector<Resource> discardRandomResource(Builder&, bool);
    void manageTrade(Builder&, Trade, std::ostream&);
    void nextTurn(std::istream&, std::ostream&);

    void printBoard() const;
    void printResidences() const;
    void printHelp() const;

    void save(std::string);

  public:
    Game(unsigned);
    Game(unsigned, std::vector<TileInitData>);
    Game(unsigned, std::vector<TileInitData>, std::vector<BuilderResourceData>, std::vector<BuilderStructureData>, int currentBuilder, int GeeseTile);
    ~Game();

    static const int NUM_BUILDERS = 4;

    int getCurrentBuilder() const;
    const std::vector<const Builder*> getBuilders() const;
    int getGeeseLocation() const;
    const Board& getBoard() const;

    void play(std::istream&, std::ostream&);
};

#endif
