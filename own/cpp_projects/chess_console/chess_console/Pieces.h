#pragma once
#include "Piece.h"

class PieceKing :
    public Piece
{

public:
    PieceKing(Color color): Piece(color, PieceType::KING) {}

    // Inherited via Piece
    virtual bool validateMove(Move move, Move lastMove, char** board) override;
};

