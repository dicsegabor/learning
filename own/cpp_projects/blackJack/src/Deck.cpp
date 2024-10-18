#include "Deck.hpp"
#include "Card.hpp"
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <vector>

Deck::Deck()
{
    cards = std::vector<Card>();

    for (int s = 0; s < 4; s++)
        for (int i = 1; i <= 13; i++)
            cards.push_back(Card(i, static_cast<Card::Suit>(s)));
}

Deck::Deck(std::vector<Card> cards) : cards(cards) {}

Card Deck::deal_card()
{
    if (cards.empty()) throw std::runtime_error("The deck is empty");

    std::srand(std::time(nullptr));
    int i     = std::rand() % cards.size();
    Card card = cards.at(i);

    cards.erase(cards.begin() + i);

    return card;
}