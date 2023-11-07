/*
* Filename: expression_tree_calculator_test.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <stdexcept>

#include "doctest.h"

#include "expression_tree_calculator.h"

#define EPSILON 10e-5

TEST_CASE("Resolver expressao posfixa")
{
    ExpressionTreeCalculator calculator;
    std::string infix = "( 3.02 + 4 ) * 2 / ( 1 - ( 5 + 2.89 ) )";
    double_t result = -2.03774;
    calculator.StoreExpression(infix);
    // Por questoes de precisao nos calculos, apenas verifico se o erro nao eh muito grande
    CHECK(calculator.Evaluation() - result <= EPSILON);
}

TEST_CASE("Lançamento de exceção: Divisão por zero")
{
    ExpressionTreeCalculator calculator;

    SUBCASE("Zero implícito na expressão")
    {
        std::string infix = "( 3.02 + 4 ) * 2 / ( ( 5 + 2.89 ) / ( 1 - 1 ) )";
        calculator.StoreExpression(infix);
        CHECK_THROWS_AS(calculator.Evaluation(), std::logic_error);
    }

    SUBCASE("Zero explícito na expressão")
    {
        std::string infix = "( 3.02 + 4 ) * 2 / ( 0 * ( 5 + 2.89 ) )";
        calculator.StoreExpression(infix);
        CHECK_THROWS_AS(calculator.Evaluation(), std::logic_error);
    }
}
