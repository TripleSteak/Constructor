#include "edge.h"
#include "../game/builder.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "vertex.h"
#include <memory>
#include <vector>
#include <stdexcept>

Edge::Edge(const Board& owner, int edgeNumber)
    : board{owner}, edgeNumber{edgeNumber}, road{nullptr} {}

Edge::~Edge() {}

void Edge::addNeighbouringTile(AbstractTile* tile) {
    neighbouringTiles.emplace_back(tile);
}

void Edge::addNeighbouringVertex(Vertex* vertex) {
    neighbouringVertices.emplace_back(vertex);
}

int Edge::getEdgeNumber() const {
    return edgeNumber;
}

std::shared_ptr<Road> Edge::getRoad() const {
    return road;
}

std::vector<Vertex*> Edge::getNeighbouringVertices() const {
    return neighbouringVertices;
}  

void Edge::canBuildRoad(int builderIndex) const {
    if (road != nullptr){
        throw std::logic_error("Road already exists at this edge");
    }
    for (Vertex* vertex : neighbouringVertices) {
        // Vertex has residence owned by builder or is connected to a road owned
        // by builder
        if (vertex->getResidence() != nullptr &&
            vertex->getResidence()->getOwner() == builderIndex) {
            return;
        }
        for (Edge* edge : vertex->getNeighbouringEdges()) {
            if (edge->getRoad() != nullptr &&
                edge->getRoad()->getOwner() == builderIndex) {
                return;
            }
        }
    }
    throw std::logic_error("No adjacent road or residence");
}   

void Edge::buildRoad(std::shared_ptr<Road> road) {
    this->road = road;
}
