#ifndef TRADE_H
#define TRADE_H

#include "resource.h"
#include <string>

struct Trade {
    std::string proposeeColour;
    int numToGive;
    Resource resourceToGive;
    int numToTake;
    Resource resourceToTake;
};

#endif
