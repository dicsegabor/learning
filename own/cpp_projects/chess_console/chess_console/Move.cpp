#include "Move.h"

Move::Move(Coordinate from, Coordinate to)
	:from(from), to(to), jump(false)
{
	if (this->from.x < 0) this->from.x = 0;
	if (this->from.y < 0) this->from.y = 0;
	if (this->to.x < 0) this->to.x = 0;
	if (this->to.y < 0) this->to.y = 0;
}

int Move::distance()
{
	return abs(from.x - to.x) + abs(from.y - to.y);
}
