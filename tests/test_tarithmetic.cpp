#include "../src/TExpressionSolver.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <string>

// --------------------------------------------------
// Construction
// --------------------------------------------------

TEST(TExpressionSolver, can_create_with_valid_expression)
{
  ASSERT_NO_THROW(TExpressionSolver solver("1+2"));
}

TEST(TExpressionSolver, empty_expression_throws)
{
  ASSERT_THROW(TExpressionSolver solver(""), std::invalid_argument);
}

// --------------------------------------------------
// Postfix conversion
// --------------------------------------------------

TEST(TExpressionSolver, converts_simple_expression_to_postfix)
{
  TExpressionSolver solver("2+3");
  std::vector<std::string> expected = { "2", "3", "+" };
  EXPECT_EQ(expected, solver.ToPostfix());
}

TEST(TExpressionSolver, respects_operator_precedence)
{
  TExpressionSolver solver("2+3*4");
  std::vector<std::string> expected = { "2", "3", "4", "*", "+" };
  EXPECT_EQ(expected, solver.ToPostfix());
}

TEST(TExpressionSolver, handles_parentheses)
{
  TExpressionSolver solver("(2+3)*4");
  std::vector<std::string> expected = { "2", "3", "+", "4", "*" };
  EXPECT_EQ(expected, solver.ToPostfix());
}

// --------------------------------------------------
// Evaluation
// --------------------------------------------------

TEST(TExpressionSolver, evaluates_simple_addition)
{
  TExpressionSolver solver("2+3");
  EXPECT_DOUBLE_EQ(5.0, solver.Evaluate());
}

TEST(TExpressionSolver, evaluates_expression_with_precedence)
{
  TExpressionSolver solver("2+3*4");
  EXPECT_DOUBLE_EQ(14.0, solver.Evaluate());
}

TEST(TExpressionSolver, evaluates_expression_with_parentheses)
{
  TExpressionSolver solver("(2+3)*4");
  EXPECT_DOUBLE_EQ(20.0, solver.Evaluate());
}

// --------------------------------------------------
// Error handling
// --------------------------------------------------

TEST(TExpressionSolver, division_by_zero_throws)
{
  TExpressionSolver solver("5/0");
  ASSERT_THROW(solver.Evaluate(), std::runtime_error);
}

TEST(TExpressionSolver, invalid_character_throws)
{
  ASSERT_THROW(TExpressionSolver solver("2+a"), std::invalid_argument);
}

TEST(TExpressionSolver, mismatched_parentheses_throw)
{
  ASSERT_THROW(TExpressionSolver solver("(2+3"), std::invalid_argument);
}
