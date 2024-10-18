#pragma once

#include "Move.h"
#include "Rules.h"

class PlayerAbstract
{
public:
	const Color color() { return color_; }
	virtual Move getMove() = 0;

private:
	Color color_;
};

