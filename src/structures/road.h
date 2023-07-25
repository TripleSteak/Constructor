#ifndef ROAD_H
#define ROAD_H

#include "../common/forward.h"

class Road final {
  private:
    int owner;
    Edge* location;

  public:
    Road(int, Edge*);
    ~Road();

    int getOwner();
    Edge* getLocation();
};

#endif