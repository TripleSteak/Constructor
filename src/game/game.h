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

    std::vector<TileInitData> generateRandomBoard();

    Builder& getBuilder(std::string);
    std::vector<Resource> discardRandomResource(Builder&, bool);

    void beginTurn(std::istream&, std::ostream&);
    void duringTurn(std::istream&, std::ostream&);
    void buildInitialResidences(std::istream&, std::ostream&);
    void moveGeese(std::istream&, std::ostream&);
    void facilitateTrade(Builder&, Trade, std::ostream&);
    void nextTurn(std::istream&, std::ostream&);

  public:
    static const int NUM_BUILDERS = 4;

    Game();
    Game(std::vector<TileInitData>);
    Game(std::vector<TileInitData>, std::vector<BuilderResourceData>, std::vector<BuilderStructureData>, int currentBuilder, int GeeseTile);
    ~Game();

    int getCurrentBuilder() const;
    const std::vector<const Builder*> getBuilders() const;
    int getGeeseLocation() const;
    const Board& getBoard() const;

    bool play(std::istream&, std::ostream&, bool);
    void save(std::string);
};

#endif
