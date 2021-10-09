#include "PostfixCalculator.h"

PostfixCalculator::PostfixCalculator()
    : stack(Stack<double>(256))
{
}

double PostfixCalculator::calculate(const std::string& expression)
{
    stack.flush();
    std::stringstream input(expression, std::ios_base::in);
    char ch;
    double operand;

    while (input.get(ch))
    {
        switch (ch)
        {
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
            input >> operand;
            stack.push(operand);
            break;

        case '+':
            stack.push(stack.pop() + stack.pop());
            break;

        case '-':
            if (std::isdigit(input.peek()))
            {
                input.putback(ch);
                input >> operand;
                stack.push(operand);
                break;
            }
            operand = stack.pop();
            stack.push(stack.pop() - operand);
            break;

        case '*':
            stack.push(stack.pop() * stack.pop());
            break;

        case '/':
            operand = stack.pop();
            if (operand == 0)
            {
                throw std::logic_error("zero division");
            }
            stack.push(stack.pop() / operand);
            break;

        case '^':
            operand = stack.pop();
            stack.push(std::pow(stack.pop(), operand));
            break;

        case '~':
            stack.push(-stack.pop());
            break;

        default:
            break;
        }
    }

    if (stack.isEmpty())
    {
        throw std::logic_error("invalid expression");
    }

    return stack.pop();
}
