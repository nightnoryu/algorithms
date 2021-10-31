#pragma once

#include "common_inc.h"

struct Domino
{
    int side1;
    int side2;
};

class DominoParser
{
public:
    static std::vector<Domino> readFromStream(std::istream& input);
};
