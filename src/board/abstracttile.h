#ifndef ABSTRACTTILE_H
#define ABSTRACTTILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <memory>
#include <vector>

class AbstractTile {
  public:
    AbstractTile();
    virtual ~AbstractTile();

    virtual void addNeighbouringVertex(Vertex*) = 0;

    virtual int getTileNumber() const = 0; // Unique identifier assigned to each tile on the board
    virtual int getTileValue() const = 0;  // The dice roll needed to obtain resources from this tile
    virtual Resource getResource() const = 0;

    virtual std::vector<int> getStealCandidates(Builder&) const = 0;
    virtual BuilderInventoryUpdate giveResourcesToBuilders() const = 0;

    virtual std::unique_ptr<AbstractTile> removeGeese() = 0;
    virtual bool hasGeese() const = 0;
};

#endif
