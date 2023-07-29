#ifndef VERTEX_H
#define VERTEX_H

#include "../common/forward.h"
#include <memory>
#include <vector>

class Vertex final {
  private:
    int vertexNumber;
    std::shared_ptr<Residence> residence;

    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Edge*> neighbouringEdges;

  public:
    Vertex(int);
    ~Vertex();

    bool operator==(const Vertex&) const;

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringEdge(Edge*);

    int getVertexNumber() const;
    std::shared_ptr<Residence> getResidence() const;
    std::vector<Edge*> getNeighbouringEdges() const;

    bool canBuildResidence(Builder&) const;
    bool canBuildInitialResidence() const;
    bool canUpgradeResidence(Builder&) const;

    void buildResidence(std::shared_ptr<Residence>);
    void upgradeResidence(std::shared_ptr<Residence>);
};

#endif
