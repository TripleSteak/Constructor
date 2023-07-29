#include "residence.h"

Residence::Residence(Builder& owner, Vertex& location) : owner{owner}, location{location} {}

Residence::~Residence() {}

Builder& Residence::getOwner() const {
    return owner;
}

Vertex& Residence::getLocation() const {
    return location;
}
