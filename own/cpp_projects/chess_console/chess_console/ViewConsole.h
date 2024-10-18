#pragma once

#include <string>
#include <iostream>

#include "Piece.h"
#include "Board.h"

class ViewConsole
{
private:
	int getColorNumber(Piece* piece);
public:
	void printBoard(Board board);
	Move inputToMove();
};

