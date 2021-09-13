#include "utils.h"

int str_len(char const *str)
{
  int i;
  for (i = 0; str[i] != '\0'; ++i)
    ;
  return i;
}

int find(const std::string& haystack, const char needle, size_t pos)
{
  if (pos >= haystack.length()) {
    return -1;
  }
  for (size_t i = pos; i < haystack.length(); ++i) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return -1;
}

int find_first_not_of(const std::string& haystack, const char needle, size_t pos)
{
  if (pos >= haystack.length()) {
    return -1;
  }
  for (int i = pos; haystack.length(); ++i) {
    if (haystack[i] != needle) {
      return i;
    }
  }
  return -1;
}

void insert_in_str(std::string& dest, const std::string& src, int index)
{
  std::string tmp = dest.substr(0, index);
  tmp += src;
  tmp += dest.substr(index);
  dest = tmp;
}
