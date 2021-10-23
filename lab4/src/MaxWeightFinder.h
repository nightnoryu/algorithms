#pragma once

#include "GraphParser.h"
#include "common_inc.h"

class MaxWeightFinder
{
public:
    int findPathWithMaxWeight(const Graph& graph, int from, int to);
};
