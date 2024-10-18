#pragma once

#include "rules.hpp"
#include <ostream>

// Used in IO
const std::map<char, Type> type_chars = {
  {'P', Type::Pawn  },
  {'B', Type::Bishop},
  {'N', Type::Knight},
  {'R', Type::Rook  },
  {'Q', Type::Queen },
  {'K', Type::King  }
};

// Used in IO
const std::map<char, Color> color_chars = {
  {'B', Color::Black},
  {'W', Color::White},
};

struct Coordinate
{
  std::size_t x, y;

  Coordinate(std::size_t x, std::size_t y) : x(x), y(y) {}

  bool operator<(const Coordinate &other) const
  {
    if (x == other.x) return y < other.y;
    return x > other.x;
  }
};

std::ostream &operator<<(std::ostream &os, const Coordinate &o);

typedef std::pair<Coordinate, Coordinate> Move;

std::ostream &operator<<(std::ostream &os, const Move &o);
