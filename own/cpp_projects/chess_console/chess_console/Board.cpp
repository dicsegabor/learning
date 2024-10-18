#include "Board.h"

Board::Board()
{
	fields_ = new Field * [s_height_];
	for (int i = 0; i < s_height_; i++)
		fields_[i] = new Field[s_width_];

	for (int r = 0; r < s_height_; r++)
		for (int c = 0; c < s_width_; c++)
			fields_[r][c] = Field(c, r);
}

void Board::addPiece(Piece* piece, Coordinate coords)
{
	getField(coords)->setPiece(piece);
}

void Board::movePiece(Move move)
{
	auto from = getField(move.from);
	auto to = getField(move.to);

	to->setPiece(from->piece());
	from->setPiece(nullptr);

	to->piece()->setMoved();
}

bool Board::validateMove(Move move, std::vector<Move> history)
{
	Move lastMove = Move();

	if (history.size() != 0)
		lastMove = history.back();

	return getField(move.from)->piece()->validateMove(move, lastMove, this->asCharArray());
}

void Board::initialize()
{
	addPiece(new PieceKing(Color::WHITE), Coordinate(0, 7));
}

char** Board::asCharArray()
{
	char** board = new char * [s_height_];
	for (int i = 0; i < s_height_; i++)
		board[i] = new char[s_width_];

	for (int r = 0; r < s_height_; r++)
	{
		for (int c = 0; c < s_width_; c++)
		{
			board[r][c] = fields_[r][c].toChar();
			// lowercase letter, if moved
			if (fields_[r][c].piece()->moved())
				board[r][c] += 32;
		}
	}

	return board;
}