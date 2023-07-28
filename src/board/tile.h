#ifndef TILE_H
#define TILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <vector>

class Tile final : public AbstractTile {
  private:
    const Board& board;
    int tileNumber;
    int tileValue;
    Resource resource;
    std::vector<Vertex*> neighbouringVertices;
    std::vector<Edge*> neighbouringEdges;

  public:
    Tile(const Board&, int, int, Resource);
    ~Tile();

    void addNeighbouringVertex(Vertex*) override;
    void addNeighbouringEdge(Edge*) override;

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    std::vector<Resource> getResourcesFromDiceRoll(const Builder&,
                                                   int) const override;
};

#endif
