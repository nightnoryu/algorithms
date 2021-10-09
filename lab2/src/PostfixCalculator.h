#pragma once

#include "stack.hpp"
#include <cmath>
#include <sstream>
#include <string>

class PostfixCalculator
{
public:
    PostfixCalculator();

    double calculate(const std::string& expression);

private:
    Stack<double> stack;
};
