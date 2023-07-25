#ifndef TOWER_H
#define TOWER_H

#include "../common/forward.h"
#include "residence.h"

class Tower final : public Residence {
public:
    Tower(int, Vertex&);
    ~Tower();

    int getBuildingPoints() const override;
    char getResidenceLetter() const override;
    int getResourceMultiplier() const override;
};

#endif
