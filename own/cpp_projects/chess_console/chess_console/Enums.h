#pragma once

enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

char PieceTypeToChar(PieceType type);

enum Color {
	WHITE, BLACK
};