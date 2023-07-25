#ifndef LOADEDDICE_H
#define LOADEDDICE_H

#include "../common/forward.h"
#include "dice.h"

class LoadedDice final : public Dice {
public:
    LoadedDice();
    ~LoadedDice();

    int rollDice() const override;
};

#endif
