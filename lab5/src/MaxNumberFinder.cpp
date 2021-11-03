#include "MaxNumberFinder.h"

bool sizeFirstLess(const std::string& s1, const std::string& s2)
{
    if (s1.size() < s2.size())
    {
        return true;
    }

    if (s1.size() > s2.size())
    {
        return false;
    }

    return s1 < s2;
}

std::string MaxNumberFinder::findMaxNumber(std::vector<Domino>& dominos)
{
    return findMaxNumberRecursive(dominos, WRONG_SIDE);
}

std::string MaxNumberFinder::findMaxNumberRecursive(
    std::vector<Domino>& dominos,
    int lastSide)
{
    std::string result;

    for (auto& d : dominos)
    {
        if (d.used)
        {
            continue;
        }

        if (lastSide == WRONG_SIDE || d.side1 == lastSide)
        {
            auto tmp = std::to_string(d.side1) + std::to_string(d.side2);
            d.used = true;
            tmp += findMaxNumberRecursive(dominos, d.side2);
            d.used = false;
            if (sizeFirstLess(result, tmp))
            {
                result = std::move(tmp);
            }
        }

        if (lastSide == WRONG_SIDE || d.side2 == lastSide)
        {
            auto tmp = std::to_string(d.side2) + std::to_string(d.side1);
            d.used = true;
            tmp += findMaxNumberRecursive(dominos, d.side1);
            d.used = false;
            if (sizeFirstLess(result, tmp))
            {
                result = std::move(tmp);
            }
        }
    }

    return result;
}
