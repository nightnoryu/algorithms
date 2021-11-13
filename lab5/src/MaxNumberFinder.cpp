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

std::string MaxNumberFinder::findMaxNumber(const std::vector<Domino>& dominos)
{
    auto dominosAndUsedFlags = pairDominosWithFlags(dominos);

    return findMaxNumberRecursive(dominosAndUsedFlags, WRONG_SIDE);
}

std::vector<DominoWithUsedFlag> MaxNumberFinder::pairDominosWithFlags(const std::vector<Domino>& dominos)
{
    std::vector<DominoWithUsedFlag> result(dominos.size());
    for (size_t i = 0; i < dominos.size(); ++i)
    {
        result[i] = { dominos[i], false };
    }

    return result;
}

std::string MaxNumberFinder::findMaxNumberRecursive(std::vector<DominoWithUsedFlag>& dominosWithUsedFlags, int lastSide)
{
    std::string result;

    for (auto& [domino, used] : dominosWithUsedFlags)
    {
        if (used)
        {
            continue;
        }

        if (lastSide == WRONG_SIDE || domino.side1 == lastSide)
        {
            auto tmp = std::to_string(domino.side1) + std::to_string(domino.side2);
            used = true;
            tmp += findMaxNumberRecursive(dominosWithUsedFlags, domino.side2);
            used = false;
            if (sizeFirstLess(result, tmp))
            {
                result = std::move(tmp);
            }
        }

        if (lastSide == WRONG_SIDE || domino.side2 == lastSide)
        {
            auto tmp = std::to_string(domino.side2) + std::to_string(domino.side1);
            used = true;
            tmp += findMaxNumberRecursive(dominosWithUsedFlags, domino.side1);
            used = false;
            if (sizeFirstLess(result, tmp))
            {
                result = std::move(tmp);
            }
        }
    }

    return result;
}
