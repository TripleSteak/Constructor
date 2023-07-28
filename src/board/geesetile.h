#ifndef GEESETILE_H
#define GEESETILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "abstracttile.h"
#include <memory>
#include <vector>

class GeeseTile final : public AbstractTile {
  private:
    std::unique_ptr<AbstractTile> tile; // Decorator pointer

  public:
    GeeseTile(std::unique_ptr<AbstractTile>);
    ~GeeseTile();

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    std::vector<Resource> getResourcesFromDiceRoll(const Builder&,
                                                   int) const override;
};

#endif
