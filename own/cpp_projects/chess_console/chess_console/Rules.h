#pragma once

#include "Field.h"
#include "Enums.h"

#include <vector>

class Rules
{
private:
	bool validateKingMove(Field** fields, Move move, std::vector<Move> history);

public:
	 int s_boardHeight = 8;
	const static int s_boardWidth = 8;

	bool validateMove(Field** fields, Move move, std::vector<Move> history);
};

