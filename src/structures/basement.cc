#include "basement.h"

Basement::Basement(int owner, Vertex& location) : Residence(owner, location) {}
Basement::~Basement() {}

int Basement::getBuildingPoints() const {
    return 1;
}
char Basement::getResidenceLetter() const {
    return 'B';
}
int Basement::getResourceMultiplier() const {
    return 1;
}
