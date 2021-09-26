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

class InfixToPostfixParser
{
public:
  InfixToPostfixParser();

  std::string parseFromStream(std::istream& input);

private:
  Stack<Token> m_operations;
  std::string m_expression;
  int m_currentNumber;

  Token getToken(std::istream& input);
};

#endif /* #ifndef INFIXTOPOSTFIXPARSER_H */
