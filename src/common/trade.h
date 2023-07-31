#ifndef TRADE_H
#define TRADE_H

#include "resource.h"
#include <string>

struct Trade {
    std::string proposee;
    Resource resourceToGive;
    Resource resourceToTake;
};

#endif
