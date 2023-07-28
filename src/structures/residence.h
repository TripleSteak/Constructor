#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "../common/forward.h"

class Residence {
  protected:
    int owner;
    Vertex& location;

  public:
    Residence(int, Vertex&);
    virtual ~Residence();

    int getOwner() const;
    Vertex& getLocation() const;

    virtual int getBuildingPoints() const = 0;
    virtual char getResidenceLetter() const = 0;
    virtual int getResourceMultiplier()
        const = 0; // How many copies of each Resource does a Builder obtain
                   // from adjacent Tiles during each dice roll?
};

#endif
