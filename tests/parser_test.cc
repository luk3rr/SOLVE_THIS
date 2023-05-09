#include <string>

#include "doctest.h"
#include "parser.hh"

TEST_CASE("Verificar se a string representa um número") {
    SUBCASE("Válidos") {
        std::string valid1 = "123.443";
        std::string valid2 = "-1234.443";
        std::string valid3 = "+20";
        std::string valid4 = "+2,0";
        std::string valid5 = "-2,0";

        CHECK(Parser::isNumber(valid1));
        CHECK(Parser::isNumber(valid2));
        CHECK(Parser::isNumber(valid3));
        CHECK(Parser::isNumber(valid4));
        CHECK(Parser::isNumber(valid5));
    }

    SUBCASE("Inválidos") {
        std::string invalid1 = "1234131a231321313.443";
        std::string invalid2 = "T1234.443";
        std::string invalid3 = "1234.44.3";
        std::string invalid4 = "a";
        std::string invalid5 = "+";
        std::string invalid6 = "210+";
        std::string invalid7 = "2-10";
        std::string invalid8 = "--";

        CHECK(!Parser::isNumber(invalid1));
        CHECK(!Parser::isNumber(invalid2));
        CHECK(!Parser::isNumber(invalid3));
        CHECK(!Parser::isNumber(invalid4));
        CHECK(!Parser::isNumber(invalid5));
        CHECK(!Parser::isNumber(invalid6));
        CHECK(!Parser::isNumber(invalid7));
        CHECK(!Parser::isNumber(invalid8));
    }
}

TEST_CASE("Validar expressão infixa") {
    SUBCASE("Operador no inicio ou fim") {
        CHECK(!Parser::infixIsValid("+ 1 * 3 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3.4 + 45 x"));
    }

    SUBCASE("Sequência de operadores no meio da string") {
        CHECK(!Parser::infixIsValid("1 * 3 + - 45"));
    }

    SUBCASE("Sequência de números sem operadores entre eles") {
        CHECK(!Parser::infixIsValid("10 1 * 3 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3 3 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3 - 45 0"));
    }

    SUBCASE("Expressão com parênteses inválidos") {
        CHECK(!Parser::infixIsValid("1 * ( 3 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3 - 45.5 )"));
        CHECK(!Parser::infixIsValid("( ( 1 * 3 - 45 )"));
        CHECK(!Parser::infixIsValid("1 * 3 ) - 45 )"));
        CHECK(!Parser::parentesesOrderIsValid(") 1 * 3 ( / 5 - 45"));
        CHECK(!Parser::parentesesOrderIsValid("1 * ) 3 / 5.3 ( - 45"));
        CHECK(!Parser::parentesesOrderIsValid("( 1 * ) ) 3 / 5.3 ( - 45"));
    }

    SUBCASE("Expressão infixa válida sem parênteses") {
        CHECK(Parser::infixIsValid("1 * 3 / 5 - 45"));
    }

    SUBCASE("Expressão infixa válida com parênteses") {
        CHECK(Parser::infixIsValid("( 1 ) * 3 / 5 - 45"));
        CHECK(Parser::infixIsValid("1 * 3 ( / ) 5 - 45"));
        CHECK(Parser::infixIsValid("1 * 3 / ( 5.3 - 45 )"));
    }

    SUBCASE("Expressão infixa inválida '.' como se fosse um número") {
        CHECK(!Parser::infixIsValid("1 * . / 5 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3 / 5.3 - ."));
    }

    SUBCASE("Expressão infixa inválida '.' como se fosse um número") {
        CHECK(!Parser::infixIsValid("1 * . / 5 - 45"));
        CHECK(!Parser::infixIsValid("1 * 3 / 5.3 - ."));
    }
}

TEST_CASE("Validar expressão posfixa") {
    SUBCASE("Operador no início da string") {
        CHECK(!Parser::postfixIsValid("+ 1 * 3 - 45"));
    }

    SUBCASE("Operando no fim da string") {
        CHECK(!Parser::postfixIsValid("1 3 * 3 + - 45"));
    }

    SUBCASE("Expressão com três operandos para um operador") {
        CHECK(!Parser::postfixIsValid("3 4 5 +"));
    }

    SUBCASE("Expressão com caracteres inválidos") {
        CHECK(!Parser::postfixIsValid("3 4 - 5 ) - +"));
    }

    SUBCASE("Expressão com caracteres inválidos") {
        CHECK(!Parser::postfixIsValid("3 4 - . - +"));
    }
}
