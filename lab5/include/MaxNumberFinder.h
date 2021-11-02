#pragma once

#include "DominoParser.h"
#include "common_inc.h"

constexpr int WRONG_SIDE = -1;

bool less(const std::string& s1, const std::string& s2);

class MaxNumberFinder
{
public:
    static std::string findMaxNumber(std::vector<Domino>& dominos, int lastSide);
};
