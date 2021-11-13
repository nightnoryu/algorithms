#pragma once

#include "DominoParser.h"
#include "common_inc.h"

struct DominoWithUsedFlag
{
    Domino domino;
    bool used = false;
};

bool sizeFirstLess(const std::string& s1, const std::string& s2);

class MaxNumberFinder
{
public:
    static std::string findMaxNumber(const std::vector<Domino>& dominos);

private:
    static constexpr int WRONG_SIDE = -1;

    static std::vector<DominoWithUsedFlag> pairDominosWithFlags(const std::vector<Domino>& dominos);

    static std::string findMaxNumberRecursive(std::vector<DominoWithUsedFlag>& dominosWithUsedFlags, int lastSide);
};
