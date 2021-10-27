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
    } while (constantMarks[to] == MARK_EMPTY);

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
    temporaryMarks.assign(graph.size(), MARK_EMPTY);
    constantMarks.assign(graph.size(), MARK_EMPTY);
    constantMarks[from] = std::numeric_limits<int>::max();
}

void MaxWeightFinder::recalculateTemporaryMarks(const Graph& graph, int i)
{
    for (int j = 0; j < graph.size(); ++j)
    {
        if (constantMarks[j] == MARK_EMPTY)
        {
            if (graph[i][j] != std::numeric_limits<int>::max())
            {
                temporaryMarks[j] = std::max(std::min(constantMarks[i], graph[i][j]), temporaryMarks[j]);
            }
        }
    }
}

int MaxWeightFinder::maxTemporaryToConstant()
{
    int k = findMaxTemporaryMark();
    if (k != -1)
    {
        if (constantMarks[k] != MARK_EMPTY)
        {
            throw std::logic_error("there are no way");
        }
        constantMarks[k] = temporaryMarks[k];
    }
    else
    {
        throw std::logic_error("there are no way");
    }

    return k;
}

int MaxWeightFinder::findMaxTemporaryMark()
{
    int max = std::numeric_limits<int>::min();
    int maxIndex = -1;
    for (int i = 0; i < temporaryMarks.size(); ++i)
    {
        if (constantMarks[i] == MARK_EMPTY && temporaryMarks[i] != MARK_EMPTY && temporaryMarks[i] > max)
        {
            max = temporaryMarks[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}
