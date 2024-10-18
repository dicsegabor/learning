#pragma once

#include <iostream>
#include <string>
#include <vector>

class Card
{
  public:
    enum class Suit
    {
        H,
        D,
        C,
        S,
    };

  private:
    int type, value;
    Suit suit;

    std::string letter() const;

  public:
    Card(int type, Suit suit);
    inline int get_value() const { return value; }

    std::string to_string() const;
};