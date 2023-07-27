#include "edge.h"
#include "../structures/road.h"

Edge::Edge(int edgeNumber) : edgeNumber{edgeNumber}, road{nullptr} {}
Edge::~Edge() { delete road; }
