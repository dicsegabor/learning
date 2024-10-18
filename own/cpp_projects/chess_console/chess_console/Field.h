#pragma once

#include "Piece.h"
#include "Move.h"

class Field
{
public:
	Field() : coords_(Coordinate(0, 0)), piece_(nullptr) {}
	Field(int x, int y) : coords_(Coordinate(x, y)), piece_(nullptr) {};

	Piece* const piece() { return piece_; }
	void setPiece(Piece* piece) { piece_ = piece; }
	const Coordinate coords() { return coords_; }
	char toChar();

	Field& operator=(const Field& other);

private:
	Piece* piece_;
	Coordinate coords_;
};

