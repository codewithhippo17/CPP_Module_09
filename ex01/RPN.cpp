#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {
  *this = other;
}

RPN &RPN::operator=(const RPN &other) {
  if (this != &other) {
    this->_stack = other._stack;
  }
  return *this;
}

RPN::~RPN() {}

std::stack<int> RPN::getStack() const {
  return this->_stack;
}

void RPN::executeExpression(const std::string &exp)
{
  for (size_t i = 0; i < exp.length(); i++)
  {
    char c = exp[i];
    if (c == ' ')
      continue;
    else if (isdigit(c))
    {
      if (i + 1 < exp.length() && exp[i + 1] != ' ')
        throw std::runtime_error("Error: Numbers must be strictly less than 10 and separated by spaces.");
      _stack.push(c - '0');
    }
    else if (c == '+' || c == '*' || c == '-' || c == '/')
    {
      if (_stack.size() < 2)
        throw std::runtime_error("Error: Insufficient operands for operator '" + std::string(1, c) + "'.");
      if (i + 1 < exp.length() && exp[i + 1] != ' ')
        throw std::runtime_error("Error: Operators must be separated by spaces.");

      int b = _stack.top(); _stack.pop();
      int a = _stack.top(); _stack.pop();

      if (c == '+') _stack.push(a + b);
      else if (c == '-') _stack.push(a - b);
      else if (c == '*') _stack.push(a * b);
      else if (c == '/') 
      {
        if (b == 0) throw std::runtime_error("Error: Division by zero is undefined.");
           _stack.push(a / b);
      }
    }
    else
      throw std::runtime_error("Error: Invalid character '" + std::string(1, c) + "' encountered.");
  }

  if (_stack.size() != 1)
    throw std::runtime_error("Error: The expression is incomplete. Too many operands remaining.");

  std::cout << _stack.top() << std::endl;
}
