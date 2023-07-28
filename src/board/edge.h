#ifndef EDGE_H
#define EDGE_H

#include "../common/forward.h"
#include <vector>

class Edge final {
  private:
    const Board* board;
    int edgeNumber;
    Road* road;
    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Vertex*> neighbouringVertices;

  public:
    Edge(const Board*, int);
    ~Edge();

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringVertex(Vertex*);

    int getEdgeNumber() const;
    Road* getRoad() const;

    bool canBuildRoad(int);
    void buildRoad(int);
};

#endif
