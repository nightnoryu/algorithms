#include "InfixToPostfixParser.h"

InfixToPostfixParser::InfixToPostfixParser(size_t stackSize)
    : operators(Stack<Token>(stackSize))
    , currentNumber(0)
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
        case Token::NUMBER:
            result += std::to_string(currentNumber);
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

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        input.putback(ch);
        input >> currentNumber;
        return Token::NUMBER;

    case '(':
        return Token::LP;

    case ')':
        return Token::RP;

    case '*':
    case '/':
    case '^':
        return Token(ch);

    case '-':
        if (std::isdigit(input.peek()))
        {
            input.putback(ch);
            input >> currentNumber;
            return Token::NUMBER;
        }
        else if (input.peek() == static_cast<char>(Token::LP))
        {
            return Token::UMINUS;
        }
        return Token(ch);

    case '+':
        if (std::isdigit(input.peek()))
        {
            input >> currentNumber;
            return Token::NUMBER;
        }
        else if (input.peek() == static_cast<char>(Token::LP))
        {
            return Token::UPLUS;
        }
        return Token(ch);

    default:
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

        if (!operators.isEmpty() && operators.peek() == Token::UMINUS)
        {
            result += tokenToString(operators.pop());
            result += ' ';
        }
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
