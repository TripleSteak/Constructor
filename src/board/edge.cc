#include "edge.h"
#include "../game/builder.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "vertex.h"
#include <vector>

using namespace std;

Edge::Edge(const Board* owner, int edgeNumber)
    : board{owner}, edgeNumber{edgeNumber}, road{nullptr} {}

Edge::~Edge() {
    delete road;
}

void Edge::addNeighbouringTile(AbstractTile* tile) {
    neighbouringTiles.emplace_back(tile);
}

void Edge::addNeighbouringVertex(Vertex* vertex) {
    neighbouringVertices.emplace_back(vertex);
}

int Edge::getEdgeNumber() const {
    return edgeNumber;
}

Road* Edge::getRoad() const {
    return road;
}

bool Edge::canBuildRoad(int builderNum) {
    if (road != nullptr) {
        return false;
    }

    for (Vertex* vertex : neighbouringVertices) {
        // Vertex has residence owned by builder or is connected to a road owned
        // by builder
        if (vertex->getResidence() != nullptr &&
            vertex->getResidence()->getOwner() == builderNum) {
            return true;
        }
        for (Edge* edge : vertex->getNeighbouringEdges()) {
            if (edge->getRoad() != nullptr &&
                edge->getRoad()->getOwner() == builderNum) {
                return true;
            }
        }
    }

    return false;
}

void Edge::buildRoad(int builderNum) {
    road = new Road(builderNum, this);
}
