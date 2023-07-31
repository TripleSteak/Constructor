#include "vertex.h"
#include "../game/builder.h"
#include "../structures/basement.h"
#include "../structures/road.h"
#include "edge.h"

Vertex::Vertex(int vertexNumber) : vertexNumber{vertexNumber}, residence{nullptr} {}
Vertex::~Vertex() {}

bool Vertex::operator==(const Vertex& other) const {
    return vertexNumber == other.vertexNumber && residence == other.residence && neighbouringEdges == other.neighbouringEdges;
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

std::vector<Edge*> Vertex::getNeighbouringEdges() const {
    return neighbouringEdges;
}

bool Vertex::canBuildResidence(Builder& builder) const {
    if (residence != nullptr) {
        // Residence already exists at this vertex!
        return false;
    }

    bool hasConnectingRoad = false;

    for (Edge* edge : neighbouringEdges) {
        if (edge->getRoad() != nullptr && edge->getRoad()->getOwner() == builder) {
            hasConnectingRoad = true;
        }

        for (Vertex* vertex : edge->getNeighbouringVertices()) {
            if (vertex->getResidence() != nullptr) {
                // Residence too close to another residence
                return false;
            }
        }
    }

    // Residence can only be built along an existing road owned by builder
    return hasConnectingRoad;
}

bool Vertex::canBuildInitialResidence() const {
    if (residence != nullptr) {
        // Residence already exists at this vertex!
        return false;
    }

    for (Edge* edge : neighbouringEdges) {
        for (Vertex* vertex : edge->getNeighbouringVertices()) {
            if (vertex->getResidence() != nullptr) {
                // Residence too close to another residence
                return false;
            }
        }
    }

    return true;
}

bool Vertex::canUpgradeResidence(Builder& builder) const {
    /*
     * In order to upgrade a residence, the following conditions must be met:
     * - A residence must exist at the vertex
     * - The residence must not already be max level (i.e. Tower)
     * - The residence must be owned by the builder
     */
    return residence != nullptr && residence->getResidenceLetter() != 'T' && residence->getOwner() == builder;
}

void Vertex::buildResidence(std::shared_ptr<Residence> residence) {
    this->residence = residence;
}

void Vertex::upgradeResidence(std::shared_ptr<Residence> residence) {
    // No need for deletion of old residence since it is a smart pointer
    this->residence = residence;
}
