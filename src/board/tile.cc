#include "tile.h"
#include <vector>

Tile::Tile(const Board& owner, int tileNumber, int tileValue, Resource resource)
    : AbstractTile(), board{owner}, tileNumber{tileNumber},
      tileValue{tileValue}, resource{resource} {}

Tile::~Tile() {}

void Tile::addNeighbouringVertex(Vertex* vertex) {
    neighbouringVertices.emplace_back(vertex);
}

void Tile::addNeighbouringEdge(Edge* edge) {
    neighbouringEdges.emplace_back(edge);
}

int Tile::getTileNumber() const {
    return tileNumber;
}

int Tile::getTileValue() const {
    return tileValue;
}

Resource Tile::getResource() const {
    return resource;
}

std::vector<Resource> Tile::getResourcesFromDiceRoll(const Builder& builder,
                                                     int rollNumber) const {
    // TODO: Implement!
    std::vector<Resource> returnVector;
    return returnVector;
}
