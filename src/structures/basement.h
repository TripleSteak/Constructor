#ifndef BASEMENT_H
#define BASEMENT_H

#include "../common/forward.h"
#include "residence.h"

class Basement final : public Residence {
  public:
    Basement(int, Vertex*);
    ~Basement();

    int getBuildingPoints() override;
    char getResidenceLetter() override;
    int getResourceMultiplier() override;
};

#endif