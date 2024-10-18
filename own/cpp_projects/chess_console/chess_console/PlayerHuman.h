#pragma once

#include "PlayerAbstract.h"

class PlayerHuman :
    public PlayerAbstract
{
    // Inherited via PlayerAbstract
    virtual Move getMove() override;
};

