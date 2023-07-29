#ifndef ROAD_H
#define ROAD_H

#include "../common/forward.h"

class Road final {
  private:
    Builder& owner;
    Edge& location;

  public:
    Road(Builder&, Edge&);
    ~Road();

    Builder& getOwner() const;
    Edge& getLocation() const;
};

#endif
