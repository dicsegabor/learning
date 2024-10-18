#include "other.hpp"

std::ostream &operator<<(std::ostream &os, const Coordinate &o)
{
  return os << "{" << o.x << ", " << o.y << "}";
}

std::ostream &operator<<(std::ostream &os, const Move &o)
{
  return os << "[" << o.first << " -> " << o.second << "]";
}
