#ifndef EDGE_H
#define EDGE_H

#include "../common/forward.h"
#include <vector>

class Edge final {
  private:
    Board* board;
    int edgeNumber;
    Road* road;

    std::vector<AbstractTile*> getNeighbouringTiles() const;
    std::vector<Vertex*> getNeighbouringVertices() const;

  public:
    Edge(int);
    ~Edge();

    void setBoard(Board&);

    int getEdgeNumber() const;
    Road* getRoad() const;

    bool canBuildRoad(const Builder&);
    void buildRoad(const Builder&);
};

#endif
