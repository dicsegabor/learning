#include "Game.hpp"
#include <iostream>

int main()
{
    Game game = Game(2);

    while (game.play_game())
        game.reset();

    return 0;
}