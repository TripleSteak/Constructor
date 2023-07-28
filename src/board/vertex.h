#ifndef VERTEX_H
#define VERTEX_H

#include "../common/forward.h"
#include <vector>

class Vertex final {
  private:
    const Board& board;
    int vertexNumber;
    std::shared_ptr<Residence> residence;

    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Edge*> neighbouringEdges;

  public:
    Vertex(const Board&, int);
    ~Vertex();

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringEdge(Edge*);

    int getVertexNumber() const;
    std::shared_ptr<Residence> getResidence() const;
    std::vector<Edge*> getNeighbouringEdges() const;

    bool canBuildResidence(const Builder&) const;
    bool canBuildInitialResidence() const;
    bool canUpgradeResidence(const Builder&) const;

    void buildResidence(const Builder&);
    void buildInitialResidence(const Builder&);
    void upgradeResidence();
};

#endif
