#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "../common/forward.h"

class Residence {
  protected:
    Builder& owner;
    Vertex& location;

  public:
    Residence(Builder&, Vertex&);
    virtual ~Residence();

    Builder& getOwner() const;
    Vertex& getLocation() const;

    virtual int getBuildingPoints() const = 0;
    virtual char getResidenceLetter() const = 0;
    virtual int getResourceMultiplier() const = 0; // How many copies of each Resource does a Builder obtain
                                                   // from adjacent Tiles during each dice roll?
};

#endif
