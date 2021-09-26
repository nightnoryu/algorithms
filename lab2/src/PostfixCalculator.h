#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include "stack.hpp"
#include <string>
#include <sstream>
#include <cmath>

class PostfixCalculator
{
public:
  PostfixCalculator();

  double calculate(const std::string& expression);

private:
  Stack<double> m_stack;
};

#endif /* #ifndef POSTFIXCALCULATOR_H */
