#pragma once

#include "common_inc.h"

struct PathWithWeight
{
    int from;
    int to;
    int weight;
};

using Graph = std::vector<std::vector<int>>;

class GraphParser
{
public:
    Graph parseFromStream(std::istream& input);

private:
    std::vector<PathWithWeight> readPaths(std::istream& input);

    void initializeGraph(Graph& graph, const std::vector<PathWithWeight>& paths);

    int findMaxNode(const std::vector<PathWithWeight>& paths);

    void fillGraph(Graph& graph, const std::vector<PathWithWeight>& paths);
};
