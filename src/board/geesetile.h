#ifndef GEESETILE_H
#define GEESETILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <memory>

class GeeseTile final : public AbstractTile {
  private:
    std::unique_ptr<Tile> tile; // Decorator pointer

  public:
    GeeseTile(std::unique_ptr<Tile>); // Can only decorate Tile objects
    ~GeeseTile();

    std::unique_ptr<Tile> removeGoose();

    void addNeighbouringVertex(Vertex*) override;

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    void giveResourcesToBuilders() const override;

    bool hasGeese() const override;
};

#endif
