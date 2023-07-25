#ifndef HOUSE_H
#define HOUSE_H

#include "../common/forward.h"
#include "residence.h"

class House final : public Residence {
public:
    House(int, Vertex*);
    ~House();

    int getBuildingPoints() override;
    char getResidenceLetter() override;
    int getResourceMultiplier() override;
};

#endif