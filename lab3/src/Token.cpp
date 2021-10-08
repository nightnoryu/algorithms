#include "Token.h"

std::string tokenToString(const Token token, const int number)
{
    std::string result;

    switch (token)
    {
    case Token::NUMBER:
        result = std::to_string(number);
        break;
    case Token::END:
        result = "END";
        break;
    case Token::PLUS:
    case Token::MINUS:
    case Token::MUL:
    case Token::DIV:
    case Token::POW:
    case Token::UMINUS:
    case Token::LP:
    case Token::RP:
        result = std::string(1, static_cast<char>(token));
        break;
    default:
        break;
    }

    return result;
}
