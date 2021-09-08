#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int
str_len(char const *str);

void
str_cat(char *dest, char const *source);

void
str_cpy(char *dest, char const *source);

void
str_ncpy(char *dest, char const *source, int num);

int
find(char const *haystack, char const needle, int pos);

int
reverse_find(char const *haystack, char const needle);

int
find_first_not_of(char const *haystack, char const needle, int pos);

int
occurs_in_str(char const *haystack, char const needle);

int
read_line(char *line, int num, FILE *input);

int
read_word(char *word, int num, FILE *input);
