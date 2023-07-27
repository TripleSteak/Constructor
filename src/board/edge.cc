#include "edge.h"
#include "../structures/road.h"

Edge::Edge(int edgeNumber) : edgeNumber{edgeNumber}, road{nullptr} {}
Edge::~Edge() { delete road; }

void Edge::setBoard(Board& board) {
    this->board = &board;
}

int Edge::getEdgeNumber() const {
    return edgeNumber;
}

Road* Edge::getRoad() const {
    return road;
}
