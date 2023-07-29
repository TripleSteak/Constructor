#ifndef BOARD_H
#define BOARD_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <iostream>
#include <vector>

// Stores information used to initialize Board Tiles
struct TileInitData {
    int tileValue;
    Resource resource;
};

class Board final {
  private:
    std::vector<AbstractTile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    int geeseTile; // Tile number that contains geese

    void setupVertices();
    void setupEdges();
    void setupTiles();

    std::string printVertex(int);
    std::string printEdge(int, bool);
    std::string printTile(int);
    std::string printResource(int);
    std::string printGeese(int);

  public:
    Board(std::vector<TileInitData>);
    ~Board();

    AbstractTile* getTile(int) const;
    Vertex* getVertex(int) const;
    Edge* getEdge(int) const;

    /**
     * TileInitData #0 is meant for Tile #0, TileInitData #1 is meant for Tile #1, etc.
     * There must be 19 elements in the TileInitData array, with exactly ONE park tile.
     *  (The park tile must have a tileValue of 7)
     */
    //void initBoard(std::vector<TileInitData>);

    bool buildRoad(Builder&, int, std::ostream&);
    bool buildResidence(Builder&, int, std::ostream&);
    bool buildInitialResidence(Builder&, int, std::ostream&);
    bool upgradeResidence(Builder&, int, std::ostream&);

    std::vector<Resource> getResourcesFromDiceRoll(const Builder&, int) const; // What the given Builder would obtain if the given rollNumber is rolled

    int getGeeseTile() const;
    void setGeeseTile(int);

    void printBoard(std::ostream&);
    //void printResidences();
};

#endif
