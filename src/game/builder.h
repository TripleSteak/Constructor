#ifndef BUILDER_H
#define BUILDER_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "../common/trade.h"
#include <vector>
#include <unordered_map>

class Builder final {
  private:
    int builderNumber;
    char builderColour;
    Dice* dice;
    
    std::vector<Residence*> residences; // Residences owned by this Builder
    std::vector<Road*> roads; // Roads owned by this Builder

  public:
    std::unordered_map<Resource, int> inventory; // How many copies of each Resource this Builder owns

    Builder(int, char);
    ~Builder();

    int getBuilderNumber();
    char getBuilderColour();
    std::string getStatus();

    int rollDice();
    void setDice(bool); // Parameter set to true means LoadedDice, otherwise FairDice

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
