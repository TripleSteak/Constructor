#ifndef TRADE_H
#define TRADE_H

#include "resource.h"
#include <string>

struct Trade {
    std::string proposeeColour;
    Resource resourceToGive;
    Resource resourceToTake;
};

#endif
