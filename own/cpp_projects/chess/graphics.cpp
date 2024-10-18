#include "graphics.hpp"

#include <cstddef>
#include <iostream>
#include <sstream>

// Dont put \n on the end of the text
std::string color_text(std::string text, Color foreground, Color background)
{
  std::stringstream ss;
  ss << "\033[" << foreground << ";" << (background + 10) << "m" << text
     << "\033[0m";
  return ss.str();
}

std::string figure_to_string(const Figure &f)
{
  switch (f.get_type())
  {
    case Type::Pawn : return "P";
    case Type::Bishop : return "B";
    case Type::Knight : return "N";
    case Type::Rook : return "R";
    case Type::Queen : return "Q";
    case Type::King : return "K";
    default : return " ";
  }
}

void print_board(const Board &b)
{
  Color dark = Color::Yellow, light = Color::Green;
  Color background = dark;

  for (size_t h = 0; h < 3 * b.HEIGHT; h++)
  {
    for (size_t w = 0; w < 5 * b.WIDTH; w++)
    {
      if (w % 5 == 2 && h % 3 == 1)
      {
        size_t x   = w / 5;
        size_t y   = h / 3;
        auto field = b.get_fields().at({x, y});
        auto f     = field.get_figure();
        if (f)
          std::cout << color_text(
            figure_to_string(*f), f->get_color(), background
          );
        else
          std::cout << color_text(" ", light, background);
      }
      else
        std::cout << color_text(" ", light, background);

      if (w % 5 == 4) background = background == dark ? light : dark;
    }
    std::cout << "\n";
    if (h % 3 == 2) background = background == dark ? light : dark;
  }
}
