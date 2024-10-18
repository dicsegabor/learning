#pragma once

#include <map>

#include "field.hpp"
#include "other.hpp"

class Board
{
  // Variables
public:
  const size_t WIDTH, HEIGHT;

private:
  std::map<Coordinate, Field> fields;

  // Methods
public:
  // Constructors
  Board(size_t width = 8, size_t height = 8);

  // Getters, setters
  const std::map<Coordinate, Field> get_fields() const { return fields; }
  int get_value() const;

  // IO
  // TODO: Creating a separate IO class
  void load(std::string file);

  // Other
  bool in_bounds(Coordinate c) const;
  bool move_figure(Move m);
};
