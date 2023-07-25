#ifndef BUILDER_H
#define BUILDER_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "../common/trade.h"
#include <vector>
#include <unordered_map>
#include <string>

class Builder final {
  private:
    int builderNumber;
    char builderColour;
    Dice* dice;

    std::vector<Residence*> residences;
    std::vector<Road*> roads;

  public:
    std::unordered_map<Resource, int> inventory;

    Builder(int, char);
    ~Builder();

    int getBuilderNumber() const;
    char getBuilderColour() const;
    int getBuildingPoints() const;
    std::string getStatus() const;

    int rollDice() const;
    void setDice(bool);

    int chooseGeeseSpot() const;
    char steal() const;
    Trade proposeTrade() const;
    bool respondToTrade() const;

    int buildRoad();
    int buildResidence();
    int buildInitialResidence();
    int upgradeResidence();
};

#endif
