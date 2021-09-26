#include "InfixToPostfixParser.h"

bool operator>(const Token t1, const Token t2)
{
  if (t1 == Token::POW) {
    return true;
  }

  if (t1 == Token::MUL || t1 == Token::DIV) {
    if (t2 == Token::PLUS || t2 == Token::MINUS) {
      return true;
    }
  }

  return false;
}

InfixToPostfixParser::InfixToPostfixParser()
  : m_operators(Stack<Token>(256)), m_currentNumber(-1) {}

std::string InfixToPostfixParser::parseFromStream(std::istream& input)
{
  std::string result;
  Token token = Token::IDLE;

  while (token != Token::END) {
    token = getToken(input);

    switch (token) {
      case Token::NUMBER:
        result += std::to_string(m_currentNumber);
        result += ' ';
        break;

      case Token::PLUS: case Token::MINUS:
      case Token::MUL: case Token::DIV: case Token::POW:
        result += dumpOperatorsWithHigherOrEqualPrecedence(token);
        m_operators.push(token);
        break;

      case Token::LP:
        m_operators.push(token);
        break;

      case Token::RP:
        result += dumpOperatorsUntilLeftParenthesis();
        break;

      default:
        break;
      }
  }

  result += dumpLeftoverOperators();

  return result;
}

Token InfixToPostfixParser::getToken(std::istream& input)
{
  char ch = 0;

  do {
    if (!input.get(ch)) {
      return Token::END;
    }
  } while (ch == ' ');

  switch (ch) {
    case 0: case '\n':
      return Token::END;

    case '0':case '1':case '2':case '3':case '4':
    case '5':case '6':case '7':case '8':case '9':
      input.putback(ch);
      input >> m_currentNumber;
      return Token::NUMBER;

    case '(':
      return Token::LP;

    case ')':
      return Token::RP;

    case '+': case '-': case '*': case '/': case '^':
      return Token(ch);

    default:
      throw std::invalid_argument(std::string("invalid token ") + ch);
  }
}

std::string InfixToPostfixParser::dumpOperatorsWithHigherOrEqualPrecedence(Token op)
{
  std::string result;
  Token token = m_operators.peek();

  while (!m_operators.isEmpty() && token != Token::LP && (token > op)) {
    result += static_cast<char>(token);
    result += ' ';

    m_operators.pop();
    token = m_operators.peek();
  }

  return result;
}

std::string InfixToPostfixParser::dumpOperatorsUntilLeftParenthesis()
{
  std::string result;
  Token token = m_operators.peek();

  try {
    while (!m_operators.isEmpty() && token != Token::LP) {
      result += static_cast<char>(token);
      result += ' ';

      m_operators.pop();
      token = m_operators.peek();
    }
    m_operators.pop();
  } catch (std::out_of_range& e) {
    throw std::logic_error("mismatched parentheses");
  }

  return result;
}

std::string InfixToPostfixParser::dumpLeftoverOperators()
{
  std::string result;
  Token token;

  while (!m_operators.isEmpty()) {
    token = m_operators.pop();
    result += static_cast<char>(token);

    if (token == Token::LP) {
      throw std::logic_error("mismatched parentheses");
    }

    if (!m_operators.isEmpty()) {
      result += ' ';
    }
  }

  return result;
}
