#pragma once

#include <vector>
#include <string>

#include "Enums.h"
#include "Move.h"

class Piece 
{
public:
	Piece(Color color, PieceType type) : color_(color), type_(type), moved_(false) {}

	const PieceType type() { return type_; }
	const Color color() { return color_; }
	const bool moved() { return moved_; }

	// Sets the moved variable to true
	void setMoved() { moved_ = true; }
	virtual bool validateMove(Move move, Move lastMove, char** board) = 0;
	char toChar() { return PieceTypeToChar(type_); }
	int value();

	Piece& operator=(const Piece& other);

private:
	PieceType type_;
	Color color_;
	bool moved_;
};

