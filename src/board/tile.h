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
    std::vector<Edge*> getNeighbouringEdges() override;
    std::vector<Vertex*> getNeighbouringVertices() override;

  public:
    Tile(Board*, int, int, Resource);
    ~Tile();

    int getTileNumber() override;
    int getTileValue() override;

    Resource getResource() override;
    std::vector<Resource> getResourcesFromDiceRoll(Builder&, int) override; // Resources to give to the Builder when dice are rolled
};

#endif