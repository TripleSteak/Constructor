#include "house.h"

House::House(Builder& owner, Vertex& location) : Residence(owner, location) {}
House::~House() {}

int House::getBuildingPoints() const {
    return 2;
}
char House::getResidenceLetter() const {
    return 'H';
}
int House::getResourceMultiplier() const {
    return 2;
}
