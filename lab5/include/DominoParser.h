#pragma once

#include "common_inc.h"

struct Domino
{
    int side1 = 0;
    int side2 = 0;
    bool used = false;
};

class DominoParser
{
public:
    static std::vector<Domino> readFromStream(std::istream& input);
};
