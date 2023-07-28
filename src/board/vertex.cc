#include "vertex.h"
#include "../structures/residence.h"
#include <memory>

Vertex::Vertex(const Board& owner, int vertexNumber)
    : board{owner}, vertexNumber{vertexNumber}, residence{nullptr} {}

Vertex::~Vertex() {}

void Vertex::addNeighbouringTile(AbstractTile* tile) {
    neighbouringTiles.emplace_back(tile);
}

void Vertex::addNeighbouringEdge(Edge* edge) {
    neighbouringEdges.emplace_back(edge);
}

int Vertex::getVertexNumber() const {
    return vertexNumber;
}

std::shared_ptr<Residence> Vertex::getResidence() const {
    return residence;
}
