#pragma once

#include "ParseLogger.h"
#include "stack.hpp"
#include <iostream>
#include <sstream>
#include <string>

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

class InfixToPostfixParser
{
public:
    InfixToPostfixParser(size_t stackSize, ParseLogger& logger);

    std::string parseFromString(const std::string& input);

    std::string parseFromStream(std::istream& input);

private:
    Token getToken(std::istream& input);

    std::string dumpOperatorsWithHigherOrEqualPrecedence(Token op);

    std::string dumpOperatorsUntilLeftParenthesis();

    std::string dumpLeftoverOperators();

    void appendToLog(const Token token, const std::string expression);

    std::string tokenString(const Token token);

    Stack<Token> m_operators;
    int m_currentNumber;
    ParseLogger& m_logger;
};
