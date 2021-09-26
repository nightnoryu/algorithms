#ifndef INFIXTOPOSTFIXPARSER_H
#define INFIXTOPOSTFIXPARSER_H

#include "stack.hpp"
#include "ParseLogger.h"
#include <iostream>
#include <string>

enum class Token {
  IDLE, END,
  NUMBER,
  POW = '^',
  MUL = '*', DIV = '/',
  PLUS = '+', MINUS = '-',
  LP = '(', RP = ')',
};


class InfixToPostfixParser
{
public:
  InfixToPostfixParser(ParseLogger& logger);

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

#endif /* #ifndef INFIXTOPOSTFIXPARSER_H */
