#include "utils.h"

int
str_len(char const *str)
{
  int i;
  for (i = 0; str[i] != '\0'; ++i)
    ;
  return i;
}

void
str_cat(char *dest, char const *source)
{
  char *ptr = dest + str_len(dest);
  while (*source != '\0') {
    *ptr++ = *source++;
  }
  *ptr = '\0';
}

void
str_cpy(char *dest, char const *source)
{
  for (int i = 0; (dest[i] = source[i]) != '\0'; ++i)
    ;
}

void
str_ncpy(char *dest, char const *source, int num)
{
  for (int i = 0; (dest[i] = source[i]) != '\0' && i < num; ++i)
    ;
}

int
find(char const *haystack, char const needle, int pos)
{
  if (pos >= str_len(haystack)) {
    return -1;
  }
  for (int i = pos; haystack[i] != '\0'; ++i) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return -1;
}

int
reverse_find(char const *haystack, char const needle)
{
  for (int i = str_len(haystack) - 1; i >= 0; --i) {
    if (haystack[i] == needle) {
      return i;
    }
  }
  return -1;
}

int
find_first_not_of(char const *haystack, char const needle, int pos)
{
  if (pos >= str_len(haystack)) {
    return -1;
  }
  for (int i = pos; haystack[i] != '\0'; ++i) {
    if (haystack[i] != needle) {
      return i;
    }
  }
  return -1;
}

int
occurs_in_str(char const *haystack, char const needle)
{
  int count = 0;
  for (int i = 0; i < str_len(haystack); ++i) {
    if (haystack[i] == needle) {
      ++count;
    }
  }
  return count;
}

int
read_line(char *line, int num, FILE *input)
{
  char c;
  int i;
  for (i = 0; i < num - 1 && (c = fgetc(input)) != EOF && c != '\n'; ++i) {
    line[i] = c;
  }
  line[i] = '\0';
  return i;
}

int
read_word(char *word, int num, FILE *input)
{
  char c;
  int i;
  for (i = 0; i < num - 1 && (c = fgetc(input)) != EOF && c != ' ' && c != '\n'; ++i) {
    word[i] = c;
  }
  word[i] = '\0';
  return i;
}
