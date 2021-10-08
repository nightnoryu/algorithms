#pragma once

#include "common_inc.h"

enum class Token
{
    IDLE,
    END,
    NUMBER,
    POW = '^',
    UMINUS = '~',
    UPLUS = '#',
    MUL = '*',
    DIV = '/',
    PLUS = '+',
    MINUS = '-',
    LP = '(',
    RP = ')',
};

std::string tokenToString(const Token token, const int number);
