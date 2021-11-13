#include "DominoParser.h"

std::vector<Domino> DominoParser::parse(std::istream& input)
{
    auto dominos = parseFromStream(input);
    if (input.fail())
    {
        throw std::invalid_argument("invalid input file format");
    }

    return dominos;
}

std::vector<Domino> DominoParser::parseFromStream(std::istream& input)
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
