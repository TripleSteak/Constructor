#ifndef TILE_H
#define TILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <vector>

class Tile final : public AbstractTile {
  private:
    Board* board;
    int tileNumber;
    int tileValue;
    Resource resource;

  protected:
    std::vector<Edge*> getNeighbouringEdges() const override;
    std::vector<Vertex*> getNeighbouringVertices() const override;

  public:
    Tile(Board*, int, int, Resource);
    ~Tile();

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    std::vector<Resource> getResourcesFromDiceRoll(const Builder&, int) const override;
};

#endif
