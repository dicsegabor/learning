#include "path_finding.hpp"
#include "utilities.hpp"

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

// The path can be reconstructed in by starting from the goal
std::map<Node, Node> breadth_first_search(
    std::map<Node, std::vector<Node>, comp> graph, Node start, Node goal
)
{
    // an expanding frontier on which we iterate
    std::queue<Node> frontier;
    // adding the startpoint
    frontier.push(start);

    // saving the path
    std::map<Node, Node> came_from = {
        {start, start}
    };

    while (!frontier.empty())
    {
        Node current = frontier.front();
        frontier.pop();

        // if we reach or goal the algorythm is finished
        if (current == goal) { break; }

        for (Node next : graph.at(current))
        {
            // if we've already benn there then we don't add it again to te frontier
            if (came_from.find(next) == came_from.end())
            {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }
    return came_from;
}

int path_length(std::map<Node, Node> paths, Node start, Node goal)
{
    int sum = 0;
    for (Node it = goal; it != start; it = paths[it]) { sum++; }

    // Removing the starting node
    return sum - 1;
}

// reconstructs the path in reverse
std::vector<Node>
reconstruct_path(std::map<Node, Node> paths, Node start, Node goal)
{
    std::vector<Node> path;
    for (Node it = goal; it != start; it = paths[it]) { path.push_back(it); }
    path.push_back(start);
    return path;
}

void print_path(
    std::vector<Node> path, const std::string *lines,
    std::pair<size_t, size_t> dimensions
)
{
    // displaying length
    std::cout << "L = " << (path.size() - 2) << "\n";

    // displaying path by nodes
    for (const auto &n : path)
    {
        std::cout << "(" << n.first << ", " << n.second << ") ";
    }
    std::cout << "\n";

    // removing first and last element, so we can see them on the map
    path.pop_back();
    path.erase(path.begin());

    // displaying path on original map
    for (size_t i = 0; i < dimensions.second; i++)
    {
        for (size_t j = 0; j < dimensions.first; j++)
        {
            if (contains<Node>(path, {j, i})) { std::cout << "@"; }
            else { std::cout << lines[i][j]; }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}