#include "ParseLogger.h"
#include <iostream>

ParseLogger::ParseLogger(size_t size)
    : tokens(new std::string[size])
    , expressions(new std::string[size])
    , stackDumps(new std::string[size])
    , size(size)
    , top(0)
{
}

ParseLogger::~ParseLogger()
{
    delete[] tokens;
    delete[] expressions;
    delete[] stackDumps;
}

void ParseLogger::addEntry(std::string token, const std::string& expression, const std::string& stackDump)
{
    if (top > size)
    {
        throw std::out_of_range("log overflow");
    }
    tokens[top] = token;
    expressions[top] = expression;
    stackDumps[top] = stackDump;
    ++top;
}

void ParseLogger::dumpLogToStream(std::ostream& output)
{
    size_t longestToken = findLongestString(tokens);
    if (longestToken < 5)
    {
        longestToken = 5;
    }
    size_t longestExpression = findLongestString(expressions);
    if (longestExpression < 10)
    {
        longestExpression = 10;
    }
    size_t longestStackDump = findLongestString(stackDumps);
    if (longestStackDump < 7)
    {
        longestStackDump = 7;
    }

    printHeader(output, longestToken, longestExpression, longestStackDump);

    for (size_t i = 0; i < top; ++i)
    {
        output << std::right << std::setw(longestToken) << tokens[i] << " | "
               << std::left << std::setw(longestExpression) << expressions[i] << " | "
               << std::left << std::setw(longestStackDump) << stackDumps[i] << std::endl;
    }
}

void ParseLogger::printHeader(std::ostream& output, size_t first, size_t second, size_t third)
{
    output << std::right << std::setw(first) << "Token"
           << std::left << std::setw(second + 3) << " | Expression"
           << std::left << std::setw(third) << " | Stack"
           << std::endl;
}

size_t ParseLogger::findLongestString(std::string const* const strings)
{
    size_t longest = 0;
    for (size_t i = 0; i < top; ++i)
    {
        if (strings[i].size() > longest)
        {
            longest = strings[i].size();
        }
    }

    return longest;
}
