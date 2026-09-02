#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

class RPN {
private:
	std::stack<int> _stack;

public:
  RPN();
  RPN(const RPN &other);
  RPN &operator=(const RPN &other);
  ~RPN();

	std::stack<int> getStack() const;
	void executeExpression(const std::string &exp);
};

#endif
