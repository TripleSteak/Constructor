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
#include "../common/trade.h"
#include <memory>
#include <sstream>

Builder::Builder(int builderNumber, char builderColour, unsigned seed) : builderNumber{builderNumber}, builderColour{builderColour}, seed{seed}, hasLoaded{true}, dice{std::unique_ptr<LoadedDice>()}, inventory{{BRICK, 0}, {ENERGY, 0}, {GLASS, 0}, {HEAT, 0}, {WIFI, 0}} {}

Builder::Builder(int builderNumber, char builderColour, unsigned seed, BuilderResourceData brd) : builderNumber{builderNumber}, builderColour{builderColour}, seed{seed}, hasLoaded{true}, dice{std::unique_ptr<LoadedDice>()}, inventory{{BRICK, brd.brickNum}, {ENERGY, brd.energyNum}, {GLASS, brd.glassNum}, {HEAT, brd.heatNum}, {WIFI, brd.wifiNum}} {}

Builder::~Builder() {}

bool Builder::operator==(const Builder& other) const {
    return builderNumber == other.builderNumber && builderColour == other.builderColour && residences == other.residences && roads == other.roads && inventory == other.inventory;
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

std::string Builder::getBuilderColourString() const {
    std::string colourString;
    switch (builderColour) {
        case 'B':
            colourString = "Blue";
            break;
        case 'Y':
            colourString = "Yellow";
            break;
        case 'O':
            colourString = "Orange";
            break;
        case 'R':
            colourString = "Red";
            break;
        default:
            colourString = "Invalid colour";
            break;
    }
    return colourString;
}

std::string Builder::getStatus() const {
    std::ostringstream oss;

    oss << getBuilderColour() << " has " << getBuildingPoints() << " building points, " << inventory.at(BRICK) << " brick, " << inventory.at(ENERGY) << " energy, " << inventory.at(GLASS) << " glass, " << inventory.at(HEAT) << " heat, and " << inventory.at(WIFI) << " WiFi.";

    return oss.str();
}

int Builder::rollDice(int roll) const {
    return dice->rollDice(roll);
}

void Builder::setDice(bool isLoaded) {
    if (isLoaded) {
        dice.reset(new LoadedDice());
        hasLoaded = true;
    }
    else {
        dice.reset(new FairDice(seed));
        hasLoaded = false;
    }
}

bool Builder::getDice() {
    if (hasLoaded) {
        return true;
    }
    else {
        return false;
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

Trade Builder::proposeTrade(std::string proposee, std::string resourceToGive, std::string resourceToTake, std::ostream& out) const {
    Trade trade;
    trade.proposeeColour = proposee;
    trade.resourceToGive = resourceFromString(resourceToGive);
    trade.resourceToTake = resourceFromString(resourceToTake);
    out << getBuilderColour() << " offers " << trade.proposeeColour << " one " << resourceToGive << " for one " << resourceToTake << "." << std::endl;
    out << "Does " << trade.proposeeColour << " accept this offer?" << std::endl;
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
