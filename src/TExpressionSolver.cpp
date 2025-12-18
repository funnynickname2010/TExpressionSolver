#include "TExpressionSolver.h"

#include <stack>
#include <cctype>
#include <stdexcept>
#include <sstream>

TExpressionSolver::TExpressionSolver()
  : expression("")
{
}

TExpressionSolver::TExpressionSolver(const std::string& expr)
  : expression(expr)
{
}


void TExpressionSolver::SetExpression(const std::string& expr)
{
  expression = expr;
}

const std::string& TExpressionSolver::GetExpression() const noexcept
{
  return expression;
}

bool TExpressionSolver::IsOperator(char c) const noexcept
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int TExpressionSolver::GetPriority(char op) const noexcept
{
  if (op == '+' || op == '-') {
    return 1;
  }
  if (op == '*' || op == '/') {
    return 2;
  }
  return 0;
}


std::vector<std::string> TExpressionSolver::ToPostfix() const
{
  std::vector<std::string> output;
  std::stack<char> ops;

  for (size_t i = 0; i < expression.length(); i++) {
    char c = expression[i];

    if (std::isspace(c)) {
      continue;
    }

    if (std::isdigit(c)) {
      std::string number;

      while (i < expression.length() &&
        (std::isdigit(expression[i]) || expression[i] == '.')) {
        number += expression[i];
        i++;
      }
      i--;

      output.push_back(number);
    }
    else if (c == '(') {
      ops.push(c);
    }
    else if (c == ')') {
      while (!ops.empty() && ops.top() != '(') {
        output.push_back(std::string(1, ops.top()));
        ops.pop();
      }

      if (ops.empty()) {
        throw std::invalid_argument("Mismatched parentheses");
      }

      ops.pop();
    }
    else if (IsOperator(c)) {
      while (!ops.empty() &&
        GetPriority(ops.top()) >= GetPriority(c)) {
        output.push_back(std::string(1, ops.top()));
        ops.pop();
      }

      ops.push(c);
    }
    else {
      throw std::invalid_argument("Invalid character in expression");
    }
  }

  while (!ops.empty()) {
    if (ops.top() == '(') {
      throw std::invalid_argument("Mismatched parentheses");
    }

    output.push_back(std::string(1, ops.top()));
    ops.pop();
  }

  return output;
}

double TExpressionSolver::Evaluate() const
{
  std::vector<std::string> postfix = ToPostfix();
  std::stack<double> values;

  for (const std::string& token : postfix) {
    if (token.length() == 1 && IsOperator(token[0])) {
      if (values.size() < 2) {
        throw std::runtime_error("Invalid expression");
      }

      double right = values.top();
      values.pop();
      double left = values.top();
      values.pop();

      switch (token[0]) {
      case '+': values.push(left + right); break;
      case '-': values.push(left - right); break;
      case '*': values.push(left * right); break;
      case '/':
        if (right == 0.0) {
          throw std::runtime_error("Division by zero");
        }
        values.push(left / right);
        break;
      }
    }
    else {
      values.push(std::stod(token));
    }
  }

  if (values.size() != 1) {
    throw std::runtime_error("Invalid expression");
  }

  return values.top();
}
