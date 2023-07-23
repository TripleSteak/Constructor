#ifndef TRADE_H
#define TRADE_H

#include "resource.h"

struct Trade {
    char proposeeColour;
    Resource resourceToGive;
    Resource resourceToTake;
};

#endif
