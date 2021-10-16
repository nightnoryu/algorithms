#include "GraphParser.h"

Graph GraphParser::parseFromStream(std::istream& input)
{
    Graph graph;
    graph.clear();

    auto paths = readPaths(input);
    initializeGraph(graph, paths);
    fillGraph(graph, paths);

    return graph;
}

std::vector<PathWithWeight> GraphParser::readPaths(std::istream& input)
{
    std::vector<PathWithWeight> paths;

    uint from, to, weight;
    while (input)
    {
        input >> from >> to >> weight;
        paths.push_back({ from, to, weight });
    }

    return paths;
}

void GraphParser::initializeGraph(Graph& graph, const std::vector<PathWithWeight>& paths)
{
    uint maxNode = findMaxNode(paths);
    for (uint i = 0; i < maxNode; ++i)
    {
        graph.push_back(std::vector<uint>(maxNode, 0));
    }

}

uint GraphParser::findMaxNode(const std::vector<PathWithWeight>& paths)
{
    std::vector<uint> nodes;
    for (auto const& path : paths)
    {
        nodes.push_back(path.from);
        nodes.push_back(path.to);
    }

    auto maxNode = std::max_element(nodes.begin(), nodes.end());

    return maxNode != nodes.end() ? *maxNode : 0;
}

void GraphParser::fillGraph(Graph& graph, const std::vector<PathWithWeight>& paths)
{
    for (auto const& path : paths)
    {
        graph[path.from - 1][path.to - 1] = path.weight;
    }
}
