#pragma once

#include <map>

enum class Type
{
  Pawn,
  Bishop,
  Knight,
  Rook,
  Queen,
  King,
};

const std::map<Type, int> type_values = {
  {Type::Pawn,   1  },
  {Type::Bishop, 3  },
  {Type::Knight, 3  },
  {Type::Rook,   5  },
  {Type::Queen,  8  },
  {Type::King,   100},
};

enum Color
{
  Black = 30,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
};
