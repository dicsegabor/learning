#include "Player.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Player::Player(std::string name)
    : state(State::Playing), name(name), cards(std::vector<Card>())
{}

void Player::add_card(Card card)
{
    cards.push_back(card);
    if (sum_card_values() > 21) state = State::Lose;
}

void Player::empty_hand()
{
    cards = std::vector<Card>();
}

int Player::sum_card_values() const
{
    int sum = 0;
    for (const auto &card : cards) sum += card.get_value();

    return sum;
}

std::string Player::to_string() const
{
    std::stringstream ss;

    ss << std::left << std::setw(6) << name << " | ";
    ss << std::left << std::setw(5) << sum_card_values() << " | ";

    for (const auto &card : cards) ss << card.to_string() + " ";

    return ss.str();
}