#pragma once

#include "rules.hpp"

class Figure
{
  // Variables
private:
  Type type;
  Color color;
  bool moved;

  // Methods
public:
  // Constructors
  Figure(Type type, Color color, bool moved = false)
    : type(type), color(color), moved(moved)
  {
  }

  // Getters, setters
  inline Type get_type() const { return type; }
  inline Color get_color() const { return color; }
  inline bool get_moved() const { return moved; }
  inline int get_value() const { return type_values.at(type); };

  // Other
  inline void set_type(Type type) { this->type = type; }
  inline void set_moved() { moved = true; }
};
