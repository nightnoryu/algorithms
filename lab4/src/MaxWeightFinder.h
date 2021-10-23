#pragma once

#include "GraphParser.h"
#include "common_inc.h"

class MaxWeightFinder
{
public:
    int findPathWithMaxWeight(const Graph& graph, int from, int to);

private:
    void initializeMarks(const Graph& graph, int from);

    void recalculateTemporaryMarks(const Graph& graph, int i);

    int maxTemporaryToConstant();

    bool hasNoMark(int node);

    std::vector<int> temporaryMarks;
    std::vector<int> constantMarks;
};
