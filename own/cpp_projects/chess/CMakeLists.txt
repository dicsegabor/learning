cmake_minimum_required(VERSION 3.0)

project(chess)

add_executable(chess main.cpp board.cpp field.cpp figure.cpp graphics.cpp other.cpp)

install(TARGETS chess RUNTIME DESTINATION bin)
