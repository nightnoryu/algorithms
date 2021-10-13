#pragma once

#include "common_inc.h"

enum class Token
{
    IDLE,
    END,
    IDENTIFIER,
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

std::string tokenToString(const Token token, const std::string identifier = "");
bool hasHigherPrecedence(const Token t1, const Token t2);
bool hasEqualPrecedence(const Token t1, const Token t2);
bool isLeftAssociative(const Token t);
