#include "utils.h"

size_t str_len(const std::string& str)
{
  const char *c_str = str.c_str();
  int i;
  for (i = 0; c_str[i] != '\0'; ++i)
    ;
  return i;
}

size_t find(const std::string& haystack, const char needle, size_t pos)
{
  if (pos >= str_len(haystack)) {
    return std::string::npos;
  }
  for (size_t i = pos; i < str_len(haystack); ++i) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return std::string::npos;
}

size_t find_first_not_of(const std::string& haystack, const char needle, size_t pos)
{
  if (pos >= str_len(haystack)) {
    return std::string::npos;
  }
  for (int i = pos; i < str_len(haystack); ++i) {
    if (haystack[i] != needle) {
      return i;
    }
  }
  return std::string::npos;
}

void insert_in_str(std::string& dest, const std::string& src, int index)
{
  std::string tmp = dest.substr(0, index);
  tmp += src;
  tmp += dest.substr(index);
  dest = tmp;
}
