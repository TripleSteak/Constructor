#include "residence.h"

Residence::Residence(int owner, Vertex& location) : owner{owner}, location{location} {}

Residence::~Residence() {}

int Residence::getOwner() const {
    return owner;
}

Vertex& Residence::getLocation() const {
    return location;
}
