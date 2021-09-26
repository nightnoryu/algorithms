#include "ParseLogger.h"

ParseLogger::ParseLogger(size_t size)
  : m_tokens(new std::string[size]), m_expressions(new std::string[size]),
    m_stackDumps(new std::string[size]), m_size(size), m_top(0) {}

ParseLogger::~ParseLogger()
{
  delete[] m_tokens;
  delete[] m_expressions;
  delete[] m_stackDumps;
}

void ParseLogger::addEntry(std::string token, const std::string& expression, const std::string& stackDump)
{
  if (m_top > m_size) {
    throw std::out_of_range("log overflow");
  }
  m_tokens[m_top] = token;
  m_expressions[m_top] = expression;
  m_stackDumps[m_top] = stackDump;
  ++m_top;
}

void ParseLogger::dumpLogToStream(std::ostream& output)
{
  size_t longestToken = findLongestString(m_tokens);
  if (longestToken < 5) {
    longestToken = 5;
  }
  size_t longestExpression = findLongestString(m_expressions);
  if (longestExpression < 11) {
    longestExpression = 11;
  }
  size_t longestStackDump = findLongestString(m_stackDumps);
  if (longestStackDump < 7) {
    longestStackDump = 7;
  }

  printHeader(output, longestToken, longestExpression, longestStackDump);

  for (size_t i = 0; i < m_top; ++i) {
    output << std::right << std::setw(longestToken) << m_tokens[i] << " | "
           << std::left << std::setw(longestExpression) << m_expressions[i] << "| "
           << std::left << std::setw(longestStackDump) << m_stackDumps[i] << std::endl;
  }
}

void ParseLogger::printHeader(std::ostream& output, size_t first, size_t second, size_t third)
{
  output << std::right << std::setw(first) << "Token"
         << std::left << std::setw(second) << " | Expression"
         << std::left << std::setw(third + 2) << " | Stack"
         << std::endl;
}

size_t ParseLogger::findLongestString(std::string const * const strings)
{
  size_t longest = 0;
  for (size_t i = 0; i < m_top; ++i) {
    if (strings[i].size() > longest) {
      longest = strings[i].size();
    }
  }

  return longest;
}
