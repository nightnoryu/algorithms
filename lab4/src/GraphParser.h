#pragma once

#include "common_inc.h"

using uint = unsigned int;

struct PathWithWeight
{
    uint from;
    uint to;
    uint weight;
};

using Graph = std::vector<std::vector<uint>>;


class GraphParser
{
public:
    Graph parseFromStream(std::istream& input);

private:
    std::vector<PathWithWeight> readPaths(std::istream& input);

    void initializeGraph(Graph& graph, const std::vector<PathWithWeight>& paths);

    uint findMaxNode(const std::vector<PathWithWeight>& paths);

    void fillGraph(Graph& graph, const std::vector<PathWithWeight>& paths);
};
