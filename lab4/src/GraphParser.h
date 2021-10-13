#pragma once

#include "common_inc.h"

using PathLength = unsigned int;

using Graph = std::vector<std::vector<PathLength>>;

class GraphParser
{
public:
    Graph parseFromStream(std::istream& input);
};
