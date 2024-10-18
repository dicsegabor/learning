// chess_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

#include "Game.h"

int main()
{
    Game game = Game();
    game.start();

    return 0;
}