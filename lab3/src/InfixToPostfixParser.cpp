#include "InfixToPostfixParser.h"

InfixToPostfixParser::InfixToPostfixParser(size_t stackSize)
    : operators(Stack<Token>(stackSize))
    , currentIdentifier("")
{
}

std::string InfixToPostfixParser::parseFromString(const std::string& input)
{
    std::stringstream inputStream(input, std::ios_base::in);
    return parseFromStream(inputStream);
}

std::string InfixToPostfixParser::parseFromStream(std::istream& input)
{
    operators.flush();
    std::string result;
    Token token = Token::IDLE;

    while (token != Token::END)
    {
        token = getToken(input);

        switch (token)
        {
        case Token::IDENTIFIER:
            result += currentIdentifier;
            result += ' ';
            break;

        case Token::PLUS:
        case Token::MINUS:
        case Token::MUL:
        case Token::DIV:
        case Token::POW:
        case Token::UMINUS:
        case Token::UPLUS:
            result += dumpOperatorsWithHigherOrEqualPrecedence(token);
            operators.push(token);
            break;

        case Token::LP:
            operators.push(token);
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

    do
    {
        if (!input.get(ch))
        {
            return Token::END;
        }
    } while (ch == ' ');

    switch (ch)
    {
    case 0:
    case '\n':
        return Token::END;

    case '(':
        return (previousToken = Token::LP);

    case ')':
        return (previousToken = Token::RP);

    case '*':
    case '/':
    case '^':
        return (previousToken = Token(ch));

    case '-':
        if (previousToken == Token::IDENTIFIER || previousToken == Token::RP)
        {
            return (previousToken = Token::MINUS);
        }
        return (previousToken = Token::UMINUS);

    case '+':
        if (previousToken == Token::IDENTIFIER || previousToken == Token::RP)
        {
            return (previousToken = Token::PLUS);
        }
        return (previousToken = Token::UPLUS);

    default:
        if (std::isalpha(ch))
        {
            input.putback(ch);
            readIdentifier(input);
            return (previousToken = Token::IDENTIFIER);
        }
        throw std::invalid_argument(std::string("invalid token ") + ch);
    }
}

std::string InfixToPostfixParser::dumpOperatorsWithHigherOrEqualPrecedence(Token op)
{
    if (operators.isEmpty())
    {
        return "";
    }

    std::string result;
    Token token = operators.peek();

    while (!operators.isEmpty()
        && token != Token::LP
        && (hasHigherPrecedence(token, op) || (hasEqualPrecedence(token, op) && isLeftAssociative(token))))
    {
        result += tokenToString(token);
        result += ' ';

        operators.pop();
        if (!operators.isEmpty())
        {
            token = operators.peek();
        }
    }

    return result;
}

std::string InfixToPostfixParser::dumpOperatorsUntilLeftParenthesis()
{
    std::string result;
    Token token = operators.peek();

    try
    {
        while (!operators.isEmpty() && token != Token::LP)
        {
            result += tokenToString(token);
            result += ' ';

            operators.pop();
            token = operators.peek();
        }
        operators.pop();
    }
    catch (std::out_of_range& e)
    {
        throw std::logic_error("mismatched parentheses");
    }

    return result;
}

std::string InfixToPostfixParser::dumpLeftoverOperators()
{
    std::string result;
    Token token;

    while (!operators.isEmpty())
    {
        token = operators.pop();
        result += tokenToString(token);

        if (token == Token::LP)
        {
            throw std::logic_error("mismatched parentheses");
        }

        if (!operators.isEmpty())
        {
            result += ' ';
        }
    }

    return result;
}

void InfixToPostfixParser::readIdentifier(std::istream& input)
{
    char ch;
    currentIdentifier = "";
    while (input.get(ch) && std::isalnum(ch))
    {
        currentIdentifier += ch;
    }
    input.putback(ch);
}
