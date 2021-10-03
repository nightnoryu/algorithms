#ifndef TOKEN_H
#define TOKEN_H

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

#endif /* #ifndef TOKEN_H */
