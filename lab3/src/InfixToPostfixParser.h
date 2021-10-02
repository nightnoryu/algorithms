#ifndef INFIXTOPOSTFIXPARSER_H
#define INFIXTOPOSTFIXPARSER_H

#include "common_inc.h"
#include "Token.h"
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

  std::string tokenString(const Token token);

  Stack<Token> m_operators;
  int m_currentNumber;
};

#endif /* #ifndef INFIXTOPOSTFIXPARSER_H */
