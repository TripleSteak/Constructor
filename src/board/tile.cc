#include "tile.h"

Tile::Tile(int tileNumber, int tileValue, Resource resource) : AbstractTile(), tileNumber{tileNumber}, tileValue{tileValue}, resource{resource} {}
Tile::~Tile() {}

std::vector<Edge*> Tile::getNeighbouringEdges() const {
    // TODO: Implement!
    std::vector<Edge*> returnVector;
    return returnVector;
}

std::vector<Vertex*> Tile::getNeighbouringVertices() const {
    // TODO: Implement!
    std::vector<Vertex*> returnVector;
    return returnVector;
}

void Tile::setBoard(Board& board) {
    this->board = &board;
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

std::vector<Resource> Tile::getResourcesFromDiceRoll(const Builder& builder, int rollNumber) const {
    // TODO: Implement!
    std::vector<Resource> returnVector;
    return returnVector;
}
