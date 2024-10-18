cmake_minimum_required(VERSION 3.10)

project(Blackjack VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Blackjack main.cpp Game.cpp Card.cpp Deck.cpp Player.cpp)