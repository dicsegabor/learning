#pragma once

#include "figure.hpp"
#include <memory>

class Field
{
  // Variables
private:
  // For managing attacks and protections on the field
  int value_modifier;
  std::unique_ptr<Figure> figure;

  // Methods
public:
  // Constructors
  inline Field() : value_modifier(0) {}
  Field(const Field &other);

  // Getters, setters
  inline int get_value() const { return value_modifier + figure->get_value(); }
  inline const Figure *get_figure() const { return figure.get(); }
  void set_figure(const Figure &f);

  // Other
  void move_figure(Field &other);
  // Maybe put into rules
  void attack_or_protect_field(const Figure &other);
};
