#include "Enums.h"

char PieceTypeToChar(PieceType type)
{
	switch (type)
	{
		case PieceType::PAWN: return 'P'; break;
		case PieceType::ROOK: return 'R'; break;
		case PieceType::KNIGHT: return 'N'; break;
		case PieceType::BISHOP: return 'B'; break;
		case PieceType::QUEEN: return 'Q'; break;
		case PieceType::KING: return 'K'; break;
		default: return ' '; break;
	}
}
