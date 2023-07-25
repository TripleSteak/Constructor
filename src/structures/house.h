#ifndef HOUSE_H
#define HOUSE_H

#include "../common/forward.h"
#include "residence.h"

class House final : public Residence {
public:
    House(int, Vertex&);
    ~House();

    int getBuildingPoints() const override;
    char getResidenceLetter() const override;
    int getResourceMultiplier() const override;
};

#endif
