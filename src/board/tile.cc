#include "tile.h"
#include "../common/inventoryupdate.h"
#include "../game/builder.h"
#include "../structures/residence.h"
#include "vertex.h"
#include <vector>
#include <algorithm>

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

BuilderInventoryUpdate Tile::giveResourcesToBuilders() const {
    // Assume that tileNumber was rolled by Dice
    BuilderInventoryUpdate update;
    for (Vertex* vertex : neighbouringVertices) {
        if (vertex->getResidence() != nullptr) {
            vertex->getResidence()->getOwner().inventory[resource] += vertex->getResidence()->getResourceMultiplier();
            update[vertex->getResidence()->getOwner().getBuilderNumber()][resource] += vertex->getResidence()->getResourceMultiplier();
        }
    }
    return update;
}

std::vector<int> Tile::getNeighbouringResidences(Builder& builder) const {
    std::vector<int> builders;
    for (Vertex* vertex : neighbouringVertices) {
        if (vertex->getResidence() != nullptr && vertex->getResidence()->getOwner().getBuilderNumber() != builder.getBuilderNumber() && vertex->getResidence()->getOwner().getInventoryNum() > 0) {
            if (std::find(builders.begin(), builders.end(), vertex->getResidence()->getOwner().getBuilderNumber()) == builders.end()){
                builders.emplace_back(vertex->getResidence()->getOwner().getBuilderNumber());
            } 
        }
    }
    return builders;
}

std::unique_ptr<AbstractTile> Tile::removeGeese() {
    // Should never be reached with good implementation
    throw std::logic_error("Invalid operation! Cannot remove geese from a non-geese tile.");
}

bool Tile::hasGeese() const {
    // Will be overridden by GeeseTile decorator when needed
    return false;
}
