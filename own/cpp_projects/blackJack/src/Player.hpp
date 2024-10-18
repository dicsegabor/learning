#pragma once

#include "Card.hpp"
#include <string>
#include <vector>

class Player
{
  public:
    enum class State
    {
        Playing,
        Win,
        Lose,
        Tie,
    };

  private:
    State state;
    std::string name;
    std::vector<Card> cards;

  public:
    Player(std::string name);

    inline std::string get_name() const { return name; }

    inline State get_state() const { return state; }

    inline size_t get_card_num() { return cards.size(); }

    inline Card get_first_card() const { return cards.front(); }

    void add_card(Card card);

    void empty_hand();

    int sum_card_values() const;

    std::string to_string() const;
};