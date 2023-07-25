#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "../common/forward.h"

class Residence {
  protected:
    int owner;
    Vertex* location;

  public:
    Residence(int, Vertex*);
    virtual ~Residence();

    int getOwner();
    Vertex* getLocation();

    virtual int getBuildingPoints() = 0;
    virtual char getResidenceLetter() = 0;
    virtual int getResourceMultiplier() = 0;
};

#endif