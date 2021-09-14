#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <locale>

size_t str_len(const std::string& str);

size_t find(const std::string& haystack, const char needle, size_t pos);

size_t find_first_not_of(const std::string& haystack, const char needle, size_t pos);

void insert_in_str(std::string& dest, const std::string& src, size_t index);

#endif /* #ifndef UTILS_H */
