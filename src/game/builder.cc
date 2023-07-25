#include "builder.h"
#include "../dice/dice.h"
#include "../structures/residence.h"

Builder::Builder(int builderNumber, char builderColour) : builderNumber{builderNumber}, builderColour{builderColour}, dice{nullptr} {}
Builder::~Builder() { delete dice; }

int Builder::getBuilderNumber() const { return builderNumber; }
char Builder::getBuilderColour() const { return builderColour; }

int Builder::getBuildingPoints() const {
    int buildingPoints = 0;
    for(auto& residence : residences) {
        buildingPoints += residence->getBuildingPoints();
    }

    return buildingPoints;
}
