#ifndef PARSELOGGER_H
#define PARSELOGGER_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <iomanip>

class ParseLogger
{
public:
  ParseLogger(size_t size);
  ~ParseLogger();

  void addEntry(std::string token, const std::string& expression, const std::string& stackDump);

  void dumpLogToStream(std::ostream& output);

private:
  void printHeader(std::ostream& output, size_t first, size_t second, size_t third);

  size_t findLongestString(std::string const * const strings);

  std::string *m_tokens;
  std::string *m_expressions;
  std::string *m_stackDumps;
  size_t m_size;
  size_t m_top;
};

#endif /* #ifndef PARSELOGGER_H */