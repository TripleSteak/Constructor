#include "vertex.h"
#include "../structures/residence.h"

Vertex::Vertex(int vertexNumber) : vertexNumber{vertexNumber}, residence{nullptr} {}
Vertex::~Vertex() { delete residence; }

void Vertex::setBoard(Board& board) {
    this->board = &board;
}

int Vertex::getVertexNumber() const {
    return vertexNumber;
}

Residence* Vertex::getResidence() const {
    return residence;
}
