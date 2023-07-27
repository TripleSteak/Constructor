#ifndef GEESETILE_H
#define GEESETILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <vector>

class GeeseTile final : public AbstractTile {
  private:
    AbstractTile* tile; // Decorator pointer

  protected:
    std::vector<Edge*> getNeighbouringEdges() const override;
    std::vector<Vertex*> getNeighbouringVertices() const override;

  public:
    GeeseTile(AbstractTile*);
    ~GeeseTile();

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    std::vector<Resource> getResourcesFromDiceRoll(const Builder&, int) const override;
};

#endif
