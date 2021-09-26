#ifndef INFIXTOPOSTFIXPARSER_H
#define INFIXTOPOSTFIXPARSER_H

#include "stack.hpp"
#include <iostream>
#include <string>

enum class Token {
  NUMBER, END, IDLE,
  PLUS = '+', MINUS = '-', MUL = '*', DIV = '/', POW = '^',
  LP = '(', RP = ')',
};

bool operator>(const Token t1, const Token t2);


class InfixToPostfixParser
{
public:
  InfixToPostfixParser();

  std::string parseFromStream(std::istream& input);

private:
  Token getToken(std::istream& input);

  std::string dumpOperatorsWithHigherOrEqualPrecedence(Token op);

  std::string dumpOperatorsUntilLeftParenthesis();

  std::string dumpLeftoverOperators();

  Stack<Token> m_operators;
  int m_currentNumber;
};

#endif /* #ifndef INFIXTOPOSTFIXPARSER_H */
