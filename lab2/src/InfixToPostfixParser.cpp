#include "InfixToPostfixParser.h"

InfixToPostfixParser::InfixToPostfixParser()
  : m_operations(Stack<Token>(256)), m_expression(""), m_currentNumber(-1) {}

std::string InfixToPostfixParser::parseFromStream(std::istream& input)
{
  std::string result;
  Token previousToken;
  Token currentToken = Token::IDLE;

  while (currentToken != Token::END) {
    currentToken = getToken(input);

    switch (currentToken) {
      case Token::NUMBER:
        result += std::to_string(m_currentNumber);
        result += ' ';
        break;

      case Token::PLUS: case Token::MINUS:
        while (!m_operations.isEmpty() && (m_operations.peek() == Token::PLUS || m_operations.peek() == Token::MINUS)) {
          previousToken = m_operations.pop();
          result += static_cast<char>(previousToken);
          result += ' ';
        }
        m_operations.push(currentToken);
        break;

      case Token::LP:
        m_operations.push(currentToken);
        break;

      case Token::RP:
        while (!m_operations.isEmpty() && m_operations.peek() != Token::LP) {
          previousToken = m_operations.pop();
          result += static_cast<char>(previousToken);
          result += ' ';
        }
        m_operations.pop();
    }
  }

  while (!m_operations.isEmpty()) {
    currentToken = m_operations.pop();
    result += static_cast<char>(currentToken);
    result += ' ';
  }

  return result;
}

Token InfixToPostfixParser::getToken(std::istream& input)
{
  char ch = 0;

  do {
    if (!input.get(ch)) {
      return Token::END;
    }
  } while (ch == ' ');;

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

    case '+': case '-':
      return Token(ch);

    default:
      throw std::invalid_argument(std::string("invalid token ") + ch);
  }
}
