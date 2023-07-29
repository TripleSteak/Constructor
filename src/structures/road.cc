#include "road.h"

Road::Road(Builder& owner, Edge& location) : owner{owner}, location{location} {}

Road::~Road() {}

Builder& Road::getOwner() const {
    return owner;
}

Edge& Road::getLocation() const {
    return location;
}
