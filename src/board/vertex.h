#ifndef VERTEX_H
#define VERTEX_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <vector>

class Vertex final {
  private:
    Board* board;
    int vertexNumber;
    Residence* residence;

    std::vector<Edge*> getNeighbouringEdges();
    std::vector<AbstractTile*> getNeighbouringTiles();

  public:
    Vertex(Board*, int);
    ~Vertex();

    int getVertexNumber();
    Residence* getResidence();

    bool canBuildResidence(Builder&);
    bool canBuildInitialResidence();
    bool canUpgradeResidence(Builder&);

    void buildResidence(Builder&);
    void buildInitialResidence(Builder&);
    void upgradeResidence();
};

#endif