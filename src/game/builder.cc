#include "builder.h"
#include "../board/edge.h"
#include "../board/vertex.h"
#include "../dice/dice.h"
#include "../dice/fairdice.h"
#include "../dice/loadeddice.h"
#include "../structures/basement.h"
#include "../structures/house.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "../structures/tower.h"
#include <memory>
#include <sstream>

Builder::Builder(int builderNumber, char builderColour) : builderNumber{builderNumber}, builderColour{builderColour}, dice{new LoadedDice()} {
    inventory.insert(std::make_pair(BRICK, 0));
    inventory.insert(std::make_pair(ENERGY, 0));
    inventory.insert(std::make_pair(GLASS, 0));
    inventory.insert(std::make_pair(HEAT, 0));
    inventory.insert(std::make_pair(WIFI, 0));
}

Builder::~Builder() {}

int Builder::getBuilderNumber() const {
    return builderNumber;
}
char Builder::getBuilderColour() const {
    return builderColour;
}

int Builder::getBuildingPoints() const {
    int buildingPoints = 0;
    for (auto& residence : residences) {
        buildingPoints += residence->getBuildingPoints();
    }

    return buildingPoints;
}

std::string Builder::getStatus() const {
    std::ostringstream oss;

    oss << builderColour << " has " << getBuildingPoints() << " building points, " << inventory.at(BRICK) << " brick, " << inventory.at(ENERGY) << " energy, " << inventory.at(GLASS) << " glass, " << inventory.at(HEAT) << " heat, and " << inventory.at(WIFI) << " WiFi.";

    return oss.str();
}

int Builder::rollDice(int roll) const {
    return dice->rollDice(roll);
}

void Builder::setDice(bool isLoaded) {
    if (isLoaded) {
        dice.reset(new LoadedDice());
    }
    else {
        dice.reset(new FairDice());
    }
}

int Builder::chooseGeeseSpot(std::istream& in, std::ostream& out) const {
    int geesePosition;
    out << "Choose where to place the GEESE." << std::endl;
    in >> geesePosition;
    return geesePosition;
}

char Builder::steal(std::istream& in, std::ostream& out) const {
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

std::shared_ptr<Road> Builder::tryBuildRoad(Edge edge) const {
    if (inventory.at(HEAT) < 1 || inventory.at(WIFI) < 1) {
        throw std::logic_error("Not enough resources to build road.");
    }
    std::shared_ptr<Road> road = std::make_shared<Road>(new Road(builderNumber, edge));
    // inventory.at(HEAT) -= 1;
    // inventory.at(WIFI) -= 1;
    // roads.push_back(road);
    return road;
}

std::shared_ptr<Residence> Builder::tryBuildResidence(Vertex vertex) const {
    if (inventory.at(BRICK) < 1 || inventory.at(ENERGY) < 1 || inventory.at(GLASS) < 1 || inventory.at(WIFI) < 1) {
        throw std::logic_error("Not enough resources to build residence.");
    }
    return std::make_shared<Residence>(new Basement(builderNumber, vertex));
}

std::shared_ptr<Residence> Builder::tryBuildInitialResidence(Vertex vertex) const {
    return std::make_shared<Residence>(new Basement(builderNumber, vertex));
}

std::shared_ptr<Residence> Builder::tryUpgradeResidence(Vertex vertex) const {
    switch (vertex.getResidence()->getResidenceLetter()) {
    case 'B':
        if (inventory.at(GLASS) < 2 || inventory.at(HEAT) < 3) {
            throw std::logic_error("Not enough resources to upgrade residence.");
        }
        return std::make_shared<Residence>(new House(builderNumber, vertex));
    case 'H':
        if (inventory.at(BRICK) < 3 || inventory.at(ENERGY) < 2 || inventory.at(GLASS) < 2 || inventory.at(HEAT) < 2 || inventory.at(WIFI) < 1) {
            throw std::logic_error("Not enough resources to upgrade residence.");
        }
        return std::make_shared<Residence>(new Tower(builderNumber, vertex));
    default:
        break;
    }
}
