#pragma once

#include "utilities.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

class Graph
{
    const char sn_charset[3]  = "tT";
    const char ep_charset[22] = "123456789abcdefABCDEF";
    const char ob_charset[3]  = "xX";

  public:
    const std::pair<size_t, size_t> dimensions;

  private:
    Node start_node;
    std::vector<Node> endpoints;
    std::map<Node, std::vector<Node>, comp> graph;

    bool out_of_bounds(Node n) const;

    void disconnect_node(Node n, std::vector<Dir> connections);

    std::vector<Node> get_neighbours(Node n, std::vector<Dir> connections);

    void add_endpoints(std::map<Node, char> endpoints);

    void add_obstacles(std::vector<Node> obstacles);

    void clear_unconnected_nodes();

  public:
    Graph(int h, int w);

    inline Node get_start_node() const { return start_node; }

    inline std::vector<Node> get_endpoints() const { return endpoints; }

    inline std::map<Node, std::vector<Node>, comp> get_graph() const { return graph; }

    void parse_string_array(const std::string *input);

    void print() const;
};