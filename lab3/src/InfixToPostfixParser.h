#pragma once

#include "Token.h"
#include "common_inc.h"
#include "stack.hpp"

class InfixToPostfixParser
{
public:
    InfixToPostfixParser(size_t stackSize);

    std::string parseFromString(const std::string& input);

    std::string parseFromStream(std::istream& input);

private:
    Token getToken(std::istream& input);

    std::string dumpOperatorsWithHigherOrEqualPrecedence(Token op);

    std::string dumpOperatorsUntilLeftParenthesis();

    std::string dumpLeftoverOperators();

    Stack<Token> operators;
    int currentNumber;
};
