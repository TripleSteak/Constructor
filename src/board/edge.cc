#include "edge.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "vertex.h"

Edge::Edge(int edgeNumber) : edgeNumber{edgeNumber}, road{nullptr} {}
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

bool Edge::canBuildRoad(int builderNumber) const {
    if (road != nullptr) {
        // Road already exists!
        return false;
    }

    for (Vertex* vertex : neighbouringVertices) {
        // Vertex has residence owned by the builder
        if (vertex->getResidence() != nullptr && vertex->getResidence()->getOwner() == builderNumber) {
            return true;
        }

        // Vertex is connected to a road owned by the builder
        for (Edge* edge : vertex->getNeighbouringEdges()) {
            if (edge->getRoad() != nullptr && edge->getRoad()->getOwner() == builderNumber) {
                return true;
            }
        }
    }

    // No adjacent road or residence!
    return false;
}

void Edge::buildRoad(std::shared_ptr<Road> road) {
    this->road = road;
}
