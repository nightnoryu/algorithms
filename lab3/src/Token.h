#pragma once

enum class Token
{
    IDLE,
    END,
    NUMBER,
    POW = '^',
    UMINUS = '~',
    MUL = '*',
    DIV = '/',
    PLUS = '+',
    MINUS = '-',
    LP = '(',
    RP = ')',
};
