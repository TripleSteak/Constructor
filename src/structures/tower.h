#ifndef TOWER_H
#define TOWER_H

#include "../common/forward.h"
#include "residence.h"

class Tower final : public Residence {
public:
    Tower(int, Vertex*);
    ~Tower();

    int getBuildingPoints() override;
    char getResidenceLetter() override;
    int getResourceMultiplier() override;
};


#endif