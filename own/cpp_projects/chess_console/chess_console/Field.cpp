#include "Field.h"

char Field::toChar()
{
	if (piece_ == nullptr)
		return ' ';
	else
		return piece_->toChar();
}

Field& Field::operator=(const Field& other)
{
	if (this == &other)
		return *this;

	piece_ = other.piece_;
	coords_ = other.coords_;

	return *this;
}