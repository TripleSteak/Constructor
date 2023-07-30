#ifndef EDGE_H
#define EDGE_H

#include "../common/forward.h"
#include "abstracttile.h"
#include "vertex.h"
#include <iostream>
#include <memory>
#include <vector>

class Edge final {
  private:
    const int edgeNumber;
    std::shared_ptr<Road> road;
    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Vertex*> neighbouringVertices;

  public:
    Edge(int);
    ~Edge();

    bool operator==(const Edge&) const;

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringVertex(Vertex*);

    int getEdgeNumber() const;
    std::shared_ptr<Road> getRoad() const;
    std::vector<Vertex*> getNeighbouringVertices() const;

    bool canBuildRoad(Builder&) const;
    void buildRoad(std::shared_ptr<Road>);
};

#endif
