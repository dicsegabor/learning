#include "field.hpp"
#include "figure.hpp"

#include <stdexcept>

Field::Field(const Field &other) : value_modifier(other.value_modifier)
{
  if (other.figure)
  {
    auto f = new Figure(*other.figure);
    figure = std::unique_ptr<Figure>(f);
  }
}

void Field::move_figure(Field &other)
{
  figure->set_moved();
  other.figure = std::move(figure);
}

void Field::set_figure(const Figure &f)
{
  if (figure) throw std::invalid_argument("A non empty field cannot be set!");
  figure = std::unique_ptr<Figure>(new Figure(f));
}

void Field::attack_or_protect_field(const Figure &other)
{
  value_modifier += other.get_type() == figure->get_type() ? 1 : -1;
}
