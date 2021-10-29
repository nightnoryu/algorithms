#pragma once

#include "GraphParser.h"
#include "common_inc.h"

constexpr int MARK_EMPTY = -1;

class MaxWeightFinder
{
public:
    int findPathWithMaxWeight(const Graph& graph, int from, int to);

    void printPath() const;

private:
    void validateNodes(const Graph& graph, int from, int to);

    void initializeMarksAndPath(const Graph& graph, int from);

    void recalculateTemporaryMarks(const Graph& graph, int i, std::vector<int>& path);

    int maxTemporaryToConstant();

    int findMaxTemporaryMark();

    void normalizePath(const Graph& graph);

    std::vector<int> temporaryMarks, constantMarks;
    std::vector<int> path;
};
