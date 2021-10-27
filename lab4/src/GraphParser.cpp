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

    int from, to, weight;
    while (input)
    {
        input >> from >> to >> weight;
        paths.push_back({ from, to, weight });
    }

    return paths;
}

void GraphParser::initializeGraph(Graph& graph, const std::vector<PathWithWeight>& paths)
{
    int maxNode = findMaxNode(paths);
    for (int i = 0; i < maxNode; ++i)
    {
        graph.push_back(std::vector<int>(maxNode, std::numeric_limits<int>::max()));
        graph[i][i] = 0;
    }
}

int GraphParser::findMaxNode(const std::vector<PathWithWeight>& paths)
{
    std::vector<int> nodes;
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
        graph[path.to - 1][path.from - 1] = path.weight;
    }
}
