#include "Token.h"

using Priority = unsigned int;

static std::unordered_map<Token, Priority> priorities = {
    { Token::POW, 3 },
    { Token::MUL, 2 },
    { Token::DIV, 2 },
    { Token::UPLUS, 1 },
    { Token::UMINUS, 1 },
    { Token::PLUS, 0 },
    { Token::MINUS, 0 },
};

std::string tokenToString(const Token token, const std::string identifier)
{
    std::string result;

    switch (token)
    {
    case Token::IDENTIFIER:
        result = identifier;
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
    case Token::UPLUS:
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
    return priorities[t1] > priorities[t2];
}

bool hasEqualPrecedence(const Token t1, const Token t2)
{
    return priorities[t1] == priorities[t2];
}

bool isLeftAssociative(const Token t)
{
    return t != Token::POW;
}
