#ifndef GEESETILE_H
#define GEESETILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <vector>

class GeeseTile final : public AbstractTile {
  private:
    AbstractTile* tile;

  protected:
    std::vector<Edge*> getNeighbouringEdges() override;
    std::vector<Vertex*> getNeighbouringVertices() override;

  public:
    GeeseTile(AbstractTile*);
    ~GeeseTile();

    int getTileNumber() override;
    int getTileValue() override;

    Resource getResource() override;
    std::vector<Resource> getResourcesFromDiceRoll(Builder&, int) override; // Resources to give to the Builder when dice are rolled
};

#endif