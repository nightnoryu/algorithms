#pragma once

#include "common_inc.h"
#include "GraphParser.h"

class MaxWeightFinder
{
public:
    std::vector<PathWithWeight> findPathWithMaxWeight(const Graph& graph, int from, int to);
};
