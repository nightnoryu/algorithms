#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

int find(const std::string& haystack, const char needle, size_t pos);

int find_first_not_of(const std::string& haystack, const char needle, size_t pos);

void insert_in_str(std::string& dest, const std::string& src, int index);

#endif /* #ifndef UTILS_H */
