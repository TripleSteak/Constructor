#ifndef ABSTRACTTILE_H
#define ABSTRACTTILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <vector>

class AbstractTile {
  protected:
    virtual std::vector<Edge*> getNeighbouringEdges() const = 0;
    virtual std::vector<Vertex*> getNeighbouringVertices() const = 0;

  public:
    AbstractTile();
    virtual ~AbstractTile();

    virtual int getTileNumber() const = 0; // Unique identifier assigned to each tile on the board
    virtual int getTileValue() const = 0; // The dice roll needed to obtain resources from this tile
    virtual Resource getResource() const = 0;
    virtual std::vector<Resource> getResourcesFromDiceRoll(const Builder&,
                                                           int) const = 0;
};

#endif
