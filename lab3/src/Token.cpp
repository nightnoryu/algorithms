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

bool hasHigherPrecedence(const Token t1, const Token t2)
{
    if (t1 == Token::POW && t2 != Token::POW)
    {
        return true;
    }

    if ((t1 == Token::UMINUS || t1 == Token::UPLUS) && (t1 != Token::UMINUS && t2 != Token::UPLUS))
    {
        return true;
    }

    if (t1 == Token::MUL || t1 == Token::DIV)
    {
        if (t2 == Token::PLUS || t2 == Token::MINUS)
        {
            return true;
        }
    }

    return false;
}

bool hasEqualPrecedence(const Token t1, const Token t2)
{
    if (t1 == t2)
    {
        return true;
    }

    if (t1 == Token::UMINUS && t2 == Token::UPLUS || t1 == Token::UPLUS && t2 == Token::UMINUS)
    {
        return true;
    }

    if (t1 == Token::PLUS && t2 == Token::MINUS || t1 == Token::MINUS && t2 == Token::PLUS)
    {
        return true;
    }

    if (t1 == Token::MUL && t2 == Token::DIV || t1 == Token::DIV && t2 == Token::MUL)
    {
        return true;
    }

    return false;
}

bool isLeftAssociative(const Token t)
{
    return t != Token::POW && t != Token::UMINUS && t != Token::UPLUS;
}

