#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <string>
#include <vector>

class Vertex {
public:
    Vertex();
    void addString(const std::string& s);
    bool containsString(const std::string& s) const;

private:
    std::map<std::string, bool> stringsSet; // Represents the set of strings
};

#endif // GRAPH_HPP