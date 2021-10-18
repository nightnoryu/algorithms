#include "MaxWeightFinder.h"

std::vector<PathWithWeight> MaxWeightFinder::findPathWithMaxWeight(const Graph& graph, int from, int to)
{
    std::vector<bool> unvisited(graph.size(), true);
    std::map<int, int> longestPath;
    std::map<int, int> previousNodes;
    for (int node = 0; node < unvisited.size(); ++node)
    {
        longestPath[node] = INT_MIN;
    }
    longestPath[from] = 0;

    while (std::any_of(unvisited.begin(), unvisited.end(), [](bool value) { return value; }))
    {
        int currentMaxNode = INT_MIN;
        for (int node = 0; node < unvisited.size(); ++node)
        {
            if (unvisited[node])
            {
                if (currentMaxNode == INT_MIN)
                {
                    currentMaxNode = node;
                }
                else if (longestPath[node] > longestPath[currentMaxNode])
                {
                    currentMaxNode = node;
                }
            }
        }

        for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
        {
            if (graph[currentMaxNode][neighbor] != INT_MIN)
            {
                int tentativeValue = longestPath[currentMaxNode] + graph[currentMaxNode][neighbor];
                if (tentativeValue > longestPath[neighbor])
                {
                    longestPath[neighbor] = tentativeValue;
                    previousNodes[neighbor] = currentMaxNode;
                }
            }
        }

        unvisited[currentMaxNode] = false;
    }

    std::vector<int> path;
    int node = to;

    while (node != from)
    {
        path.push_back(node);
        node = previousNodes[node];
    }
    path.push_back(from);
    std::reverse(path.begin(), path.end());

    std::cout << "longest: " << longestPath[to] << std::endl;
    for (auto const& node : path)
    {
        std::cout << node + 1 << std::endl;
    }

    return std::vector<PathWithWeight>();
}
