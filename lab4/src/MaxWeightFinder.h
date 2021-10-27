#pragma once

#include "GraphParser.h"
#include "common_inc.h"

using Marks = std::vector<int>;
constexpr int MARK_EMPTY = -1;

class MaxWeightFinder
{
public:
    int findPathWithMaxWeight(const Graph& graph, int from, int to);

private:
    void validateNodes(const Graph& graph, int from, int to);

    void initializeMarks(const Graph& graph, int from);

    void recalculateTemporaryMarks(const Graph& graph, int i);

    int maxTemporaryToConstant();

    int findMaxTemporaryMark();

    Marks temporaryMarks, constantMarks;
};
