#ifndef BUILDER_H
#define BUILDER_H

#include "../common/forward.h"
#include "../common/resource.h"
#include "../common/trade.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Stores information used to initialize builder
struct BuilderResourceData {
    int brickNum;
    int energyNum;
    int glassNum;
    int heatNum;
    int wifiNum;
};

struct BuilderStructureData {
    std::vector<std::pair<int, char>> residences;
    std::vector<int> roads;
};

class Builder final {
  private:
    const int builderNumber;
    const char builderColour;
    const unsigned seed;
    std::unique_ptr<Dice> dice;

  public:
    std::vector<std::shared_ptr<Residence>> residences;
    std::vector<std::shared_ptr<Road>> roads;
    std::unordered_map<Resource, int> inventory; // "PARK" should never be one of the keys in this map

    Builder(int, char, unsigned);
    Builder(int, char, unsigned, BuilderResourceData);
    ~Builder();

    bool operator==(const Builder&) const;

    int getBuilderNumber() const;
    char getBuilderColour() const;
    int getBuildingPoints() const;
    std::string getStatus() const;

    int rollDice(int) const;
    void setDice(bool);

    int chooseGeeseSpot(std::istream&, std::ostream&) const; // Select tile number to place geese on
    char steal(std::istream&, std::ostream&) const;          // Select which other Builder to steal from
    Trade proposeTrade(std::istream&, std::ostream&) const;
    bool respondToTrade(std::istream&, std::ostream&) const;

    std::unordered_map<Resource, int> getResourcesFromDiceRoll(int);
    std::shared_ptr<Road> tryBuildRoad(Edge);
    std::shared_ptr<Residence> tryBuildResidence(Vertex);
    std::shared_ptr<Residence> tryBuildInitialResidence(Vertex);
    std::shared_ptr<Residence> tryUpgradeResidence(Vertex);
};

#endif
