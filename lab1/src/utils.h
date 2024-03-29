#pragma once

#include <fstream>
#include <iostream>
#include <locale>
#include <string>

size_t str_len(const std::string& str);

size_t find(const std::string& haystack, const char needle, size_t pos);

size_t find_first_not_of(const std::string& haystack, const char needle, size_t pos);

void insert_in_str(std::string& dest, const std::string& src, size_t index);
