#include "InfixToPostfixParser.h"

bool hasHigherPrecedence(const Token t1, const Token t2)
{
    if (t1 == Token::POW && t2 != Token::POW)
    {
        return true;
    }

    if (t1 == Token::UMINUS && t2 != Token::UMINUS)
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
    return t != Token::POW && t != Token::UMINUS;
}

InfixToPostfixParser::InfixToPostfixParser(size_t stackSize, ParseLogger& logger)
    : operators(Stack<Token>(stackSize))
    , currentNumber(0)
    , logger(logger)
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

        if (token != Token::END)
        {
            appendToLog(token, result);
        }
    }

    result += dumpLeftoverOperators();
    appendToLog(token, result);

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

    case '+':
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
        && (hasHigherPrecedence(token, op)
            || (hasEqualPrecedence(token, op) && isLeftAssociative(token))))
    {
        result += static_cast<char>(token);
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
            result += static_cast<char>(token);
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
        result += static_cast<char>(token);

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

void InfixToPostfixParser::appendToLog(const Token token, const std::string expression)
{
    std::string stackDump;
    Token const* const stack = operators.data();
    size_t size = operators.size();

    for (size_t i = 0; i < size; ++i)
    {
        stackDump += static_cast<char>(stack[i]);
        if (i + 1 != size)
        {
            stackDump += ' ';
        }
    }

    logger.addEntry(tokenString(token), expression, stackDump);
}

std::string InfixToPostfixParser::tokenString(const Token token)
{
    switch (token)
    {
    case Token::NUMBER:
        return std::to_string(currentNumber);

    case Token::END:
        return "END";

    case Token::PLUS:
    case Token::MINUS:
    case Token::MUL:
    case Token::DIV:
    case Token::POW:
    case Token::UMINUS:
    case Token::LP:
    case Token::RP:
        return std::string(1, static_cast<char>(token));

    default:
        break;
    }

    return "";
}
