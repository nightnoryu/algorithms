#ifndef UTILS_H
#define UTILS_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAXLINE 1000
#define MAXWORD 100

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

void
insert_in_str(char *dest, char const *str, int index);

int
read_line(char *line, int num, FILE *input);

int
read_word(char *word, int num, FILE *input);

#endif /* #ifndef UTILS_H */