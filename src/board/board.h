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

    bool canBuildRoad(const Builder&, int) const;
    bool canBuildResidence(const Builder&, int) const;
    bool canBuildInitialResidence(int) const;
    bool canUpgradeResidence(const Builder&, int) const;

    void buildRoad(const Builder&, int);
    void buildResidence(const Builder&, int);
    void buildInitialResidence(const Builder&, int);
    void upgradeResidence(int);

    std::vector<Resource> getResourcesFromDiceRoll(const Builder&, int) const;

    int getGeeseTile() const;
    void setGeeseTile(int);

    void printBoard();
    void printResidences();
};

#endif
