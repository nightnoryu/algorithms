#include "DominoParser.h"

std::vector<Domino> DominoParser::readFromStream(std::istream& input)
{
    int n;
    input >> n;

    std::vector<Domino> dominos(n);
    for (auto& domino : dominos)
    {
        input >> domino.side1 >> domino.side2;
    }

    return dominos;
}
