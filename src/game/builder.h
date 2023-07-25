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
    std::unordered_map<Resource, int> inventory;

    Builder(int, char);
    ~Builder();

    int getBuilderNumber() const;
    char getBuilderColour() const;
    int getBuildingPoints() const;
    std::string getStatus() const;

    int rollDice() const;
    void setDice(bool);

    int chooseGeeseSpot(std::istream&, std::ostream&) const;
    char steal(std::istream&, std::ostream&) const;
    Trade proposeTrade(std::istream&, std::ostream&) const;
    bool respondToTrade(std::istream&, std::ostream&) const;

    int tryBuildRoad(std::istream&, std::ostream&);
    int tryBuildResidence(std::istream&, std::ostream&);
    int tryBuildInitialResidence(std::istream&, std::ostream&);
    int tryUpgradeResidence(std::istream&, std::ostream&);
};

#endif
