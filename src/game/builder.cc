#include "builder.h"
#include "../dice/dice.h"
#include "../dice/loadeddice.h"
#include "../dice/fairdice.h"
#include "../structures/residence.h"
#include <sstream>

Builder::Builder(int builderNumber, char builderColour) : builderNumber{builderNumber}, builderColour{builderColour}, dice{new LoadedDice()} {
    inventory.insert(std::make_pair(BRICK, 0));
    inventory.insert(std::make_pair(ENERGY, 0));
    inventory.insert(std::make_pair(GLASS, 0));
    inventory.insert(std::make_pair(HEAT, 0));
    inventory.insert(std::make_pair(WIFI, 0));
}

Builder::~Builder() {
    delete dice;
}

int Builder::getBuilderNumber() const {
    return builderNumber;
}
char Builder::getBuilderColour() const {
    return builderColour;
}

int Builder::getBuildingPoints() const {
    int buildingPoints = 0;
    for(auto& residence : residences) {
        buildingPoints += residence->getBuildingPoints();
    }

    return buildingPoints;
}

std::string Builder::getStatus() const {
    std::ostringstream oss;

    oss << builderColour << " has " << getBuildingPoints() << " building points, "
        << inventory.at(BRICK) << " brick, "
        << inventory.at(ENERGY) << " energy, "
        << inventory.at(GLASS) << " glass, "
        << inventory.at(HEAT) << " heat, and "
        << inventory.at(WIFI) << " WiFi.";

    return oss.str();
}

int Builder::rollDice(int roll) const {
    return dice->rollDice(roll);
}

void Builder::setDice(bool isLoaded) {
    delete dice;

    if(isLoaded) { dice = new LoadedDice(); }
    else { dice = new FairDice(); }
}

int Builder::chooseGeeseSpot(std::istream& in, std::ostream& out) const {
    int geesePosition;
    out << "Choose where to place the GEESE." << std::endl;
    in >> geesePosition;
    return geesePosition;
}

char Builder::steal(std::istream&in, std::ostream& out) const {
    char stealFrom;
    out << "Choose a builder to steal from." << std::endl;
    in >> stealFrom;
    return stealFrom;
}

Trade Builder::proposeTrade(std::istream& in, std::ostream& out) const {
    Trade trade;
    in >> trade.proposeeColour >> trade.resourceToGive >> trade.resourceToTake;
    return trade;
}

bool Builder::respondToTrade(std::istream& in, std::ostream& out) const {
    std::string response;
    out << "Does " << builderColour << " accept this offer?" << std::endl;
    in >> response;
    return response == "yes";
}

int Builder::tryBuildRoad(std::istream& in) const {
    int edgeNumber;
    in >> edgeNumber;
    return edgeNumber;
}

int Builder::tryBuildResidence(std::istream& in) const {
    int vertexNumber;
    in >> vertexNumber;
    return vertexNumber;
}

int Builder::tryBuildInitialResidence(std::istream& in) const {
    int vertexNumber;
    in >> vertexNumber;
    return vertexNumber;
}

int Builder::tryUpgradeResidence(std::istream& in) const {
    int vertexNumber;
    in >> vertexNumber;
    return vertexNumber;
}
