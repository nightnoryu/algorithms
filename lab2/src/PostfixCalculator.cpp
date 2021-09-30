#include "PostfixCalculator.h"

PostfixCalculator::PostfixCalculator()
  : m_stack(Stack<double>(256)) {}

double PostfixCalculator::calculate(const std::string& expression)
{
  m_stack.flush();
  std::stringstream input(expression, std::ios_base::in);
  char ch;
  double operand;

  while (input.get(ch)) {
    switch (ch) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        input.putback(ch);
        input >> operand;
        m_stack.push(operand);
        break;

      case '+':
        m_stack.push(m_stack.pop() + m_stack.pop());
        break;

      case '-':
        if (std::isdigit(input.peek())) {
          input.putback(ch);
          input >> operand;
          m_stack.push(operand);
          break;
        }
        operand = m_stack.pop();
        m_stack.push(m_stack.pop() - operand);
        break;

      case '*':
        m_stack.push(m_stack.pop() * m_stack.pop());
        break;

      case '/':
        operand = m_stack.pop();
        if (operand == 0) {
          throw std::logic_error("zero division");
        }
        m_stack.push(m_stack.pop() / operand);
        break;

      case '^':
        operand = m_stack.pop();
        m_stack.push(std::pow(m_stack.pop(), operand));
        break;

      case '~':
        m_stack.push(-m_stack.pop());
        break;

      default:
        break;
    }
  }

  if (m_stack.isEmpty()) {
    throw std::logic_error("invalid expression");
  }

  return m_stack.pop();
}
