#ifndef VERTEX_H
#define VERTEX_H

#include "../common/forward.h"
#include <vector>
#include <memory>

class Vertex final {
  private:
    int vertexNumber;
    std::shared_ptr<Residence> residence;

    std::vector<AbstractTile*> neighbouringTiles;
    std::vector<Edge*> neighbouringEdges;

  public:
    Vertex(int);
    ~Vertex();

    void addNeighbouringTile(AbstractTile*);
    void addNeighbouringEdge(Edge*);

    int getVertexNumber() const;
    std::shared_ptr<Residence> getResidence() const;
    std::vector<Edge*> getNeighbouringEdges() const;

    bool canBuildResidence(int) const;
    bool canBuildInitialResidence() const;
    bool canUpgradeResidence(int) const;

    void buildResidence(std::shared_ptr<Residence>);  
    void upgradeResidence(std::shared_ptr<Residence>);
};

#endif
