#include <iostream>
#include <string>

#include "graph.hpp"
#include "path_finding.hpp"

int main()
{
    int h, w;
    std::cin >> h;
    std::cin >> w;

    Graph g = Graph(h, w);

    // cin leaves a newline character, so we ignore it
    std::cin.ignore();

    // Read all 'h' lines
    std::string lines[h];
    for (int i = 0; i < h; i++) getline(std::cin, lines[i]);
    g.parse_string_array(lines);

    int sum = 0;

    for (const auto &ep : g.get_endpoints())
    {
        auto paths =
            breadth_first_search(g.get_graph(), g.get_start_node(), ep);

        sum += path_length(paths, g.get_start_node(), ep);
        print_path(
            reconstruct_path(paths, g.get_start_node(), ep), lines, g.dimensions
        );
    }

    std::cout << sum << "\n";
}
