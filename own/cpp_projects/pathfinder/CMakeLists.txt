cmake_minimum_required(VERSION 3.0)

project(pathfinder)

add_executable(pathfinder main.cpp graph.cpp path_finding.cpp utilities.cpp)

install(TARGETS pathfinder RUNTIME DESTINATION bin)
