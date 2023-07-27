#ifndef VERTEX_H
#define VERTEX_H

#include "../common/forward.h"
#include <vector>

class Vertex final {
  private:
    Board* board;
    int vertexNumber;
    Residence* residence;

    std::vector<Edge*> getNeighbouringEdges() const;
    std::vector<AbstractTile*> getNeighbouringTiles() const;

  public:
    Vertex(int);
    ~Vertex();

    void setBoard(Board&);

    int getVertexNumber() const;
    Residence* getResidence() const;

    bool canBuildResidence(const Builder&) const;
    bool canBuildInitialResidence() const;
    bool canUpgradeResidence(const Builder&) const;

    void buildResidence(const Builder&);
    void buildInitialResidence(const Builder&);
    void upgradeResidence();
};

#endif
