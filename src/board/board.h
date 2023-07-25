#ifndef BOARD_H
#define BOARD_H

#include "../common/forward.h"
#include "../common/resource.h"
#include <vector>

class Board final {
  private:
    std::vector<AbstractTile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    int geeseTile;

  public:
    Board();
    ~Board();

    void initBoard();

    bool canBuildRoad(Builder&, int);
    bool canBuildResidence(Builder&, int);
    bool canBuildInitialResidence(int);
    bool canUpgradeResidence(Builder&, int);

    void buildRoad(Builder&, int);
    void buildResidence(Builder&, int);
    void buildInitialResidence(Builder&, int);
    void upgradeResidence(int);

    std::vector<Resource> getResourcesFromDiceRoll(Builder&, int);

    int getGeeseTile();
    void setGeeseTile(int);

    void printBoard();
    void printResidences();
};

#endif