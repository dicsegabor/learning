#pragma once

#include "utilities.hpp"
#include <map>
#include <vector>
#include <string>

std::map<Node, Node> breadth_first_search(
    std::map<Node, std::vector<Node>, comp> graph, Node start, Node goal
);

int path_length(std::map<Node, Node> paths, Node start, Node goal);

std::vector<Node> reconstruct_path(std::map<Node, Node> paths, Node start, Node goal);

void print_path(std::vector<Node> path, const std::string *lines, std::pair<size_t, size_t> dimensions);