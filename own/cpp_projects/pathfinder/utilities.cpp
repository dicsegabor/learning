#include "utilities.hpp"

#include <vector>

// Convert hexa char to int, works with lower and uppercase letters
int hex_char_to_uint(char c)
{
    return c > '9' ? (c > 'F' ? c - 87 : c - 55) : c - '0';
}

std::vector<std::pair<int, int>> get_connections(char hexa, bool invert)
{
    auto connection_type = hex_char_to_uint(hexa);

    // inversion funcionality for later disconnecting nodes
    if (invert) connection_type = ~connection_type;

    // Iterating over the 4 bits, and adding appropriate connections
    std::vector<std::pair<int, int>> connections;
    for (int i = 0; i < 4; i++)
    {
        if (connection_type & 0b0001) connections.push_back(dirs[i]);
        connection_type = connection_type >> 1;
    }

    return connections;
}

bool contains(const char *charset, const char c)
{
    for (int i = 0; charset[i] != '\0'; i++)
        if (charset[i] == c) return true;

    return false;
}