#pragma once

#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>

class ParseLogger
{
public:
    ParseLogger(size_t size);
    ~ParseLogger();

    void addEntry(std::string token, const std::string& expression, const std::string& stackDump);

    void dumpLogToStream(std::ostream& output);

private:
    void printHeader(std::ostream& output, size_t first, size_t second, size_t third);

    size_t findLongestString(std::string const* const strings);

    std::string* tokens;
    std::string* expressions;
    std::string* stackDumps;
    size_t size;
    size_t top;
};
