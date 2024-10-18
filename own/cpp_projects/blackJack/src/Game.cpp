#include "Game.hpp"
#include "Player.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#define CLEAR_SCREEN std::cout << "\x1B[2J\x1B[H";

void Game::display_dealer_hided() const
{
    std::cout << std::left << std::setw(6) << dealer.get_name() << " | ??    | "
              << dealer.get_first_card().to_string() << " ??\n";
}

void Game::deal_card_for(Player &player) { player.add_card(deck.deal_card()); }

Game::Game(size_t number_of_players) : dealer(Player("Dealer"))
{
    for (size_t i = 1; i <= number_of_players; i++)
        players.push_back(Player("P" + std::to_string(i)));

    deck = Deck();
}

void Game::reset()
{
    dealer.empty_hand();
    for (auto &p : players) p.empty_hand();
    deck = Deck();
}

void Game::initial_deal()
{
    deal_card_for(dealer);
    deal_card_for(dealer);

    for (auto &player : players)
    {
        deal_card_for(player);
        deal_card_for(player);
    }
}

void Game::deal_for_all()
{
    for (auto &player : players)
    {
        CLEAR_SCREEN
        std::cout << player.to_string() << "\n";

        while (boolean_question("Do you want to draw an additional card?"))
        {
            player.add_card(deck.deal_card());

            if (player.get_state() == Player::State::Lose) break;

            CLEAR_SCREEN
            std::cout << player.to_string() << "\n";
        }
    }

    wait_for_enter();
}

void Game::deal_for_the_dealer()
{
    while (dealer.sum_card_values() < 17) deal_card_for(dealer);
}

void Game::check_winner()
{
    std::vector<Player> still_in_play;
    std::copy_if(
        players.begin(), players.end(), std::back_inserter(still_in_play),
        [](const Player &p) { return p.get_state() != Player::State::Lose; }
    );

    std::sort(
        still_in_play.begin(), still_in_play.end(),
        [](const Player &p1, const Player &p2)
        { return p1.sum_card_values() > p2.sum_card_values(); }
    );

    int dealer_sum = dealer.sum_card_values();

    if(still_in_play.empty()) std::cout << "The dealer wins!";
    else if (still_in_play.empty() && dealer_sum > 21) std::cout << "No winners!";
    else if(dealer_sum > still_in_play[0].sum_card_values()) 
        std::cout << "The dealer wins!";
}

bool Game::play_game()
{
    initial_deal();
    print();
    deal_for_all();
    print();
    deal_for_the_dealer();
    print(false);
    check_winner();
    print(false);
    return boolean_question("Do you want to start a new game?");
}

void Game::print(bool hide_dealer_card) const
{
    CLEAR_SCREEN
    std::cout << "Name   | Point | Cards\n"
              << "-------|-------|------\n";

    if (hide_dealer_card)
        display_dealer_hided();
    else
        std::cout << dealer.to_string() << "\n";

    std::cout << "-------|-------|------\n";

    for (const auto &player : players) std::cout << player.to_string() << "\n";

    wait_for_enter();
}

bool Game::boolean_question(std::string question) const
{
    std::string answer;

    while (!(answer == "y" || answer == "n"))
    {
        std::cout << question + " (y/n): ";
        std::cin >> answer;
    }
    return answer == "y";
}

void Game::wait_for_enter() const
{
    std::cout << "\nPress Enter to Continue...";
    std::cin.ignore();
}