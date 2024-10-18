#pragma once

#include "board.hpp"
#include "figure.hpp"
#include <string>

std::string color_text(std::string text, Color foreground, Color background);
std::string figure_to_string(const Figure &f);
void print_board(const Board &b);
