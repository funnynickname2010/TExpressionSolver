#pragma once

#include <string>
#include <vector>

class TExpressionSolver
{
private:
  std::string expression;

  bool IsOperator(char c) const noexcept;
  int GetPriority(char op) const noexcept;

public:
  TExpressionSolver();
  explicit TExpressionSolver(const std::string& expr);

  void SetExpression(const std::string& expr);
  const std::string& GetExpression() const noexcept;

  std::vector<std::string> ToPostfix() const;
  double Evaluate() const;
};
