#pragma once

#include <math.h>

struct Coordinate {
	int x, y;

	Coordinate() { Coordinate(0, 0); }
	Coordinate(int x, int y): x(x), y(y) {}

	bool operator==(const Coordinate& other) { return x == other.x && y == other.y; };
};

struct Move {
	Coordinate from, to;
	bool jump;

	Move() { Move(Coordinate(), Coordinate()); }
	Move(Coordinate from, Coordinate to);

	int distance();

	bool operator==(const Move& other) { return from == other.from && to == other.to; };
};