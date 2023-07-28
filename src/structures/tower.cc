#include "tower.h"

Tower::Tower(int owner, Vertex& location) : Residence(owner, location) {}

Tower::~Tower() {}

int Tower::getBuildingPoints() const {
    return 3;
}

char Tower::getResidenceLetter() const {
    return 'T';
}

int Tower::getResourceMultiplier() const {
    return 3;
}
