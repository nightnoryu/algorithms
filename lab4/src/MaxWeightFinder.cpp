#include "MaxWeightFinder.h"

int MaxWeightFinder::findPathWithMaxWeight(const Graph& graph, int from, int to)
{
    validateNodes(graph, from, to);
    initializeMarks(graph, from);
    int i = from;

    do
    {
        recalculateTemporaryMarks(graph, i);
        i = maxTemporaryToConstant();
    } while (hasNoMark(to));

    return constantMarks[to];
}

void MaxWeightFinder::validateNodes(const Graph& graph, int from, int to)
{
    if (from >= graph.size())
    {
        throw std::logic_error("invalid departure node");
    }

    if (to >= graph.size())
    {
        throw std::logic_error("invalid destination node");
    }
}

void MaxWeightFinder::initializeMarks(const Graph& graph, int from)
{
    temporaryMarks.assign(graph.size(), -1);
    constantMarks.assign(graph.size(), -1);
    constantMarks[from] = std::numeric_limits<int>::max();
}

void MaxWeightFinder::recalculateTemporaryMarks(const Graph& graph, int i)
{
    for (int j = 0; j < graph.size(); ++j)
    {
        if (graph[i][j] != std::numeric_limits<int>::max())
        {
            temporaryMarks[j] = std::max(std::min(constantMarks[i], graph[i][j]), temporaryMarks[j]);
        }
    }
}

int MaxWeightFinder::maxTemporaryToConstant()
{
    auto maxD = std::max_element(temporaryMarks.begin(), temporaryMarks.end());
    int k;
    if (maxD != temporaryMarks.end())
    {
        k = std::distance(temporaryMarks.begin(), maxD);
        constantMarks[k] = *maxD;
        temporaryMarks[k] = -1;
    }
    else
    {
        throw std::logic_error("there are no way");
    }

    return k;
}

bool MaxWeightFinder::hasNoMark(int node)
{
    return constantMarks[node] == -1;
}
