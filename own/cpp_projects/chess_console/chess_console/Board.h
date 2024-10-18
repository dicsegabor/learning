#pragma once

#include "Pieces.h"
#include "Field.h"
#include "Move.h"

class Board{
private:
	const static int s_height_ = 8, s_width_ = 8;

	Field** fields_;
public:
	Board();

	Field** fields() { return fields_; };
	const int height() const { return s_height_; }
	const int width() const { return s_width_; }

	Field* getField(Coordinate coords) { return &fields_[coords.y][coords.x]; };
	void addPiece(Piece* piece, Coordinate coords);
	void movePiece(Move move);
	bool validateMove(Move move, std::vector<Move> history);
	void initialize();
	char** asCharArray();
};

