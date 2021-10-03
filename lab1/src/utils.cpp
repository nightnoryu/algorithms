#include "utils.h"

size_t str_len(const std::string& str)
{
    const char* c_str = str.c_str();

    int i;
    for (i = 0; c_str[i] != '\0'; ++i)
        ;

    return i;
}

size_t find(const std::string& haystack, const char needle, size_t pos)
{
    if (pos >= str_len(haystack))
    {
        return std::string::npos;
    }

    for (size_t i = pos; i < str_len(haystack); ++i)
    {
        if (haystack[i] == needle)
        {
            return i;
        }
    }

    return std::string::npos;
}

size_t find_first_not_of(const std::string& haystack, const char needle, size_t pos)
{
    if (pos >= str_len(haystack))
    {
        return std::string::npos;
    }

    for (int i = pos; i < str_len(haystack); ++i)
    {
        if (haystack[i] != needle)
        {
            return i;
        }
    }

    return std::string::npos;
}

std::string substr(const std::string& src, size_t index = 0, size_t len = std::string::npos)
{
    std::string result;

    if (len == std::string::npos)
    {
        len = str_len(src);
    }
    else
    {
        len += index;
    }

    for (int i = index; i < len; ++i)
    {
        result += src.at(i);
    }

    return result;
}

void insert_in_str(std::string& dest, const std::string& src, size_t index)
{
    std::string tmp = substr(dest, 0, index);
    tmp += src;
    tmp += substr(dest, index);
    dest = tmp;
}
