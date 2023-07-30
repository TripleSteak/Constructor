#include "tile.h"
#include "../game/builder.h"
#include "../structures/residence.h"
#include "vertex.h"

Tile::Tile(int tileNumber, int tileValue, Resource resource) : AbstractTile(), tileNumber{tileNumber}, tileValue{tileValue}, resource{resource} {}

Tile::~Tile() {}

void Tile::addNeighbouringVertex(Vertex* vertex) {
    neighbouringVertices.emplace_back(vertex);
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

void Tile::giveResourcesToBuilders() const {
    // Assume that tileNumber was rolled by Dice
    for (Vertex* vertex : neighbouringVertices) {
        if (vertex->getResidence() != nullptr) {
            vertex->getResidence()->getOwner().inventory[resource] += vertex->getResidence()->getResourceMultiplier();
        }
    }
}

bool Tile::hasGeese() const {
    // Will be overridden by GeeseTile decorator when needed
    return false;
}
