#ifndef GEESETILE_H
#define GEESETILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"

class GeeseTile final : public AbstractTile {
  private:
    std::unique_ptr<AbstractTile> tile; // Decorator pointer

  public:
    GeeseTile(std::unique_ptr<AbstractTile>);
    ~GeeseTile();

    void addNeighbouringVertex(Vertex*) override;

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    BuilderInventoryUpdate giveResourcesToBuilders() const override;

    std::unique_ptr<AbstractTile> removeGeese() override;
    bool hasGeese() const override;
};

#endif
