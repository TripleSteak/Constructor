#include "edge.h"
#include "../game/builder.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "vertex.h"

Edge::Edge(int edgeNumber) : edgeNumber{edgeNumber}, road{nullptr} {}
Edge::~Edge() {}

bool Edge::operator==(const Edge& other) const {
    return edgeNumber == other.edgeNumber && road == other.road && neighbouringVertices == other.neighbouringVertices;
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

bool Edge::canBuildRoad(Builder& builder) const {
    if (road != nullptr) {
        // Road already exists!
        return false;
    }

    for (Vertex* vertex : neighbouringVertices) {
        // If the neighbouring vertex has a residence...
        // - Return true if the residence belongs to the builder
        // - Only check for adjacent roads if the vertex is empty
        if (vertex->getResidence() != nullptr) {
            if (vertex->getResidence()->getOwner() == builder) {
                return true;
            } else {
                continue;
            }
        }

        // Vertex is connected to a road owned by the builder
        // The above code body ensures that we don't build through someone else's residence
        for (Edge* edge : vertex->getNeighbouringEdges()) {
            if (edge->getRoad() != nullptr && edge->getRoad()->getOwner() == builder) {
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
