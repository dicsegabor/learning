#include "graphics.hpp"
#include "other.hpp"

int main()
{
  Board b = Board();
  b.load("saves/default_board.txt");
  print_board(b);
  b.move_figure({Coordinate(0, 1), Coordinate(0, 2)});
  print_board(b);
  return 0;
}
