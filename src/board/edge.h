#ifndef EDGE_H
#define EDGE_H

#include "../common/forward.h"
#include <memory>
#include <vector>

class Edge final {
  private:
    const Board& board;
    int edgeNumber;
    std::shared_ptr<Road> road;
    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Vertex*> neighbouringVertices;

  public:
    Edge(const Board&, int);
    ~Edge();

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringVertex(Vertex*);

    int getEdgeNumber() const;
    std::shared_ptr<Road> getRoad() const;
    std::vector<Vertex*> getNeighbouringVertices() const;
    
    void canBuildRoad(int) const;
    void buildRoad(std::shared_ptr<Road>);
};

#endif
