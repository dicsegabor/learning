#pragma once

#include "Card.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

class Deck
{
    std::vector<Card> cards;

  public:
    Deck();
    Deck(std::vector<Card> cards);

    Card deal_card();
};