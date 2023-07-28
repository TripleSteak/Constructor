#include "road.h"

Road::Road(int owner, Edge* location) : owner{owner}, location{location} {}
Road::~Road() {}

int Road::getOwner() const {
    return owner;
}
Edge* Road::getLocation() const {
    return location;
}
