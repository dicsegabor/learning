#include "Piece.h"

// Sets the values for the minmax algorhytm
int Piece::value()
{
	switch (type_)
	{
		case PieceType::PAWN: return 1; break;
		case PieceType::ROOK: return 5; break;
		case PieceType::KNIGHT: return 3; break;
		case PieceType::BISHOP: return 3; break;
		case PieceType::QUEEN: return 8; break;
		case PieceType::KING: return 1000; break;
		default: return 1; break;
	}
}

Piece& Piece::operator=(const Piece& other)
{
	if (this == &other)
		return *this;

	type_ = other.type_;
	color_ = other.color_;

	return *this;
}