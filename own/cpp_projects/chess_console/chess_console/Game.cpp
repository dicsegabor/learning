#include <windows.h>

#include "Game.h"

Game::Game()
{
	board_ = Board();
	board_.initialize();
	playerWhite_ = new PlayerHuman();
	playerBlack_ = new PlayerHuman();
}

void Game::start()
{
	while (!checkForEnd())
	{
		round();
	}
}

bool Game::round()
{
	view_.printBoard(board_);
	auto move = view_.inputToMove();
	if (board_.validateMove(move, history_))
	{
		board().movePiece(move);
		history_.push_back(move);
		std::cout << "\x1B[2J\x1B[H";

		return true;
	}

	return false;
}

bool Game::checkForEnd()
{
	return false;
}
