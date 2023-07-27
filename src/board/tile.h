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

  public:
    Tile(int, int, Resource);
    ~Tile();

    void setBoard(Board&);

    int getTileNumber() const override;
    int getTileValue() const override;
    Resource getResource() const override;
    std::vector<Resource> getResourcesFromDiceRoll(const Builder&, int) const override;
};

#endif
