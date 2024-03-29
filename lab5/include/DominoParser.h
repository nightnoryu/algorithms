#pragma once

#include "common_inc.h"

struct Domino
{
    int side1 = 0;
    int side2 = 0;
};

class DominoParser
{
public:
    static std::vector<Domino> parse(std::istream& input);

private:
    static std::vector<Domino> parseFromStream(std::istream& input);
};
