#ifndef BUILDER_H
#define BUILDER_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "../common/trade.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

class Builder final {
  private:
    int builderNumber;
    char builderColour;
    Dice* dice;

  public:
    std::vector<Residence*> residences;
    std::vector<Road*> roads;
    std::unordered_map<Resource, int> inventory; // "PARK" should never be one of the keys in this map

    Builder(int, char);
    ~Builder();

    int getBuilderNumber() const;
    char getBuilderColour() const;
    int getBuildingPoints() const;
    std::string getStatus() const;

    int rollDice(int) const;
    void setDice(bool);

    int chooseGeeseSpot(std::istream&, std::ostream&) const; // Select tile number to place geese on
    char steal(std::istream&, std::ostream&) const; // Select which other Builder to steal from
    Trade proposeTrade(std::istream&, std::ostream&) const;
    bool respondToTrade(std::istream&, std::ostream&) const;

    int tryBuildRoad(std::istream&) const;
    int tryBuildResidence(std::istream&) const;
    int tryBuildInitialResidence(std::istream&) const;
    int tryUpgradeResidence(std::istream&) const;
};

#endif
