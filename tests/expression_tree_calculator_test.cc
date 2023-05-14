#include "doctest.h"
#include "expression_tree_calculator.hh"
#include "expression_tree_calculator_excpt.hh"

TEST_CASE("Resolver expressao posfixa") {
    ExpressionTreeCalculator calculator;
    std::string infix = "( 3.02 + 4 ) * 2 / ( 1 - ( 5 + 2.89 ) )";
    long double result = -2.03774;
    calculator.storeExpression(infix);
    // Por questoes de precisao nos calculos, apenas verifico se o erro nao eh muito grande
    CHECK(calculator.evaluation() - result <= 0.0001);
}

TEST_CASE("Lançamento de exceção: Divisão por zero") {
    ExpressionTreeCalculator calculator;

    SUBCASE("Zero implícito na expressão") {
        std::string infix = "( 3.02 + 4 ) * 2 / ( ( 5 + 2.89 ) / ( 1 - 1 ) )";
        calculator.storeExpression(infix);
        CHECK_THROWS_AS(calculator.evaluation(), clcexcpt::DivisionByZero);
    }
    SUBCASE("Zero explícito na expressão") {
        std::string infix = "( 3.02 + 4 ) * 2 / ( 0 * ( 5 + 2.89 ) )";
        calculator.storeExpression(infix);
        CHECK_THROWS_AS(calculator.evaluation(), clcexcpt::DivisionByZero);
    }
}
