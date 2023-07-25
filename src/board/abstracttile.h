#ifndef ABSTRACTTILE_H
#define ABSTRACTTILE_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <vector>

class AbstractTile {
  protected:
    virtual std::vector<Edge*> getNeighbouringEdges() = 0;
    virtual std::vector<Vertex*> getNeighbouringVertices() = 0;

  public:
    AbstractTile();
    virtual ~AbstractTile();

    virtual int getTileNumber() = 0;
    virtual int getTileValue() = 0;

    virtual Resource getResource() = 0;
    virtual std::vector<Resource> getResourcesFromDiceRoll(Builder&, int) = 0; // Resources to give to the Builder when dice are rolled
};

#endif