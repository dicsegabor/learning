#pragma once

#include "ViewConsole.h"
#include "PlayerHuman.h"
#include "Board.h"

#include <vector>

class Game
{
	ViewConsole view_;

	PlayerAbstract * playerWhite_, * playerBlack_;
	Board board_;
	std::vector<Move> history_;

public:
	Game();

	ViewConsole view() { return view_; }
	Board board() { return board_; }

	void start();
	bool round();
	bool checkForEnd();
};

