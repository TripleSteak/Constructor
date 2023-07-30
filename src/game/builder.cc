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

bool Builder::operator==(const Builder& other) const {
    return builderNumber == other.builderNumber && builderColour == other.builderColour && residences == other.residences && roads == other.roads &&
           inventory == other.inventory;
}

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

    oss << builderColour << " has " << getBuildingPoints() << " building points, " << inventory.at(BRICK) << " brick, " << inventory.at(ENERGY)
        << " energy, " << inventory.at(GLASS) << " glass, " << inventory.at(HEAT) << " heat, and " << inventory.at(WIFI) << " WiFi.";

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

std::shared_ptr<Road> Builder::tryBuildRoad(Edge edge) {
    if (inventory.at(HEAT) < 1 || inventory.at(WIFI) < 1) {
        return nullptr;
    }
    std::shared_ptr<Road> road = std::make_shared<Road>(*this, edge);
    inventory.at(HEAT) -= 1;
    inventory.at(WIFI) -= 1;
    roads.emplace_back(road);
    return road;
}

std::shared_ptr<Residence> Builder::tryBuildResidence(Vertex vertex) {
    if (inventory.at(BRICK) < 1 || inventory.at(ENERGY) < 1 || inventory.at(GLASS) < 1 || inventory.at(WIFI) < 1) {
        return nullptr;
    }
    std::shared_ptr<Residence> residence = std::make_shared<Basement>(*this, vertex);
    inventory.at(BRICK) -= 1;
    inventory.at(ENERGY) -= 1;
    inventory.at(GLASS) -= 1;
    inventory.at(WIFI) -= 1;
    residences.emplace_back(residence);
    return residence;
}

std::shared_ptr<Residence> Builder::tryBuildInitialResidence(Vertex vertex) {
    std::shared_ptr<Residence> residence = std::make_shared<Basement>(*this, vertex);
    residences.emplace_back(residence);
    return residence;
}

std::shared_ptr<Residence> Builder::tryUpgradeResidence(Vertex vertex) {
    std::shared_ptr<Residence> residence;
    switch (vertex.getResidence()->getResidenceLetter()) {
        case 'B':
            if (inventory.at(GLASS) < 2 || inventory.at(HEAT) < 3) {
                return nullptr;
            }
            residence = std::make_shared<House>(*this, vertex);
            inventory.at(GLASS) -= 2;
            inventory.at(HEAT) -= 3;
            for (size_t i = 0; i < residences.size(); i++) {
                if (residences[i]->getLocation().getVertexNumber() == vertex.getVertexNumber()) {
                    residences[i] = residence;
                    return residence;
                }
            }
        case 'H':
            if (inventory.at(BRICK) < 3 || inventory.at(ENERGY) < 2 || inventory.at(GLASS) < 2 || inventory.at(HEAT) < 2 || inventory.at(WIFI) < 1) {
                return nullptr;
            }
            residence = std::make_shared<Tower>(*this, vertex);
            inventory.at(BRICK) -= 3;
            inventory.at(ENERGY) -= 2;
            inventory.at(GLASS) -= 2;
            inventory.at(HEAT) -= 2;
            inventory.at(WIFI) -= 1;
            for (size_t i = 0; i < residences.size(); i++) {
                if (residences[i]->getLocation().getVertexNumber() == vertex.getVertexNumber()) {
                    residences[i] = residence;
                    return residence;
                }
            }
        default:
            return nullptr;
            break;
    }
}
