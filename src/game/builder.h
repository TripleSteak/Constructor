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

    int getBuilderNumber();
    char getBuilderColour();
    std::string getStatus();

    int rollDice();
    void setDice(bool);

    int chooseGeeseSpot();
    char steal();
    Trade proposeTrade();
    bool respondToTrade();

    int buildRoad();
    int buildResidence();
    int buildInitialResidence();
    int upgradeResidence();
};

#endif
