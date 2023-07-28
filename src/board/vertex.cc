#include "vertex.h"
#include "edge.h"
#include "../structures/road.h"
#include "../structures/residence.h"
#include "../structures/basement.h"
#include <memory>
#include <vector>
#include <stdexcept>    

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

std::vector<Edge*> Vertex::getNeighbouringEdges() const{
    return neighbouringEdges;
}

void Vertex::canBuildResidence(int builderIndex) const {
    if (residence != nullptr){
        throw std::logic_error("Residence already exists at this vertex");
    }
    for (Edge* edge : neighbouringEdges) {
        if (edge->getRoad() != nullptr &&
            edge->getRoad()->getOwner() == builderIndex) {
            
            for (Vertex* vertex : edge->getNeighbouringVertices()) {
                if (vertex->getResidence() != nullptr) {
                    throw std::logic_error("Residence too close to another residence");
                }
            }
        }
    }
}

void Vertex::canBuildInitialResidence() const{
    if (residence != nullptr){
        throw std::logic_error("Residence already exists at this vertex");
    }
    for (Edge* edge : neighbouringEdges) {
        for (Vertex* vertex : edge->getNeighbouringVertices()) {
            if (vertex->getResidence() != nullptr) {
                throw std::logic_error("Residence too close to another residence");
            }
        }
    }
 }

void Vertex::canUpgradeResidence(int builderIndex) const {
    if (residence == nullptr) {
        throw std::logic_error("No residence to upgrade");
    }
    if (residence->getResidenceLetter() == 'T') {
        throw std::logic_error("Cannot upgrade further");
    }
    if (residence->getOwner() != builderIndex) {
        throw std::logic_error("Cannot upgrade residence owned by another builder");
    }
}

 void Vertex::buildResidence(std::shared_ptr<Residence> residence) {
    this->residence = residence;
 }


void Vertex::upgradeResidence(std::shared_ptr<Residence> res) {
    if (residence->getResidenceLetter() == 'B') {
        residence.reset();
        residence = res;
    }
    else if (residence->getResidenceLetter() == 'H') {
        residence.reset();
        residence = res;
    }
}
