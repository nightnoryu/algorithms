#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

uint
str_len(char const *str);

void
str_cat(char *dest, char const *source);

void
str_cpy(char *dest, char const *source);

void
str_ncpy(char *dest, char const *source, int num);

int
reverse_find(char const *haystack, char const needle);

uint
occurs_in_str(char const *haystack, char const needle);

uint
read_line(char *line, int num, FILE *input);
