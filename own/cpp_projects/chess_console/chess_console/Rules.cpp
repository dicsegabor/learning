#include "Rules.h"

bool Rules::validateMove(Field** fields, Move move, std::vector<Move> history)
{
    // Check if it is the first move
    if (history.size() == 0);

	switch (fields[move.from.x][move.from.y].piece()->type())
	{
		case PieceType::PAWN:
			break;
		case PieceType::ROOK:
			break;
		case PieceType::KNIGHT:
			break;
		case PieceType::BISHOP:
			break;
		case PieceType::QUEEN:
			break;
		case PieceType::KING:
			break;
		default: return false; break;
	}
}
