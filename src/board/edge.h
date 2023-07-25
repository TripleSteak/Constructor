#ifndef EDGE_H
#define EDGE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <vector>

class Edge final {
  private:
    Board* board;
    int edgeNumber;
    Road* road;

    std::vector<AbstractTile*> getNeighbouringTiles();
    std::vector<Vertex*> getNeighbouringVertices();

  public:
    Edge(Board*, int);
    ~Edge();

    int getEdgeNumber();
    Road* getRoad();

    bool canBuildRoad(Builder&);
    void buildRoad(Builder&);
};

#endif