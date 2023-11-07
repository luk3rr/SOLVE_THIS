/*
* Filename: parser_test.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include <string>

#include "doctest.h"
#include "parser.h"

TEST_CASE("Verificar se a string representa um número")
{
    SUBCASE("Válidos")
    {
        std::string valid1 = "123.443";
        std::string valid2 = "-1234.443";
        std::string valid3 = "+20";
        std::string valid4 = "+2,0";
        std::string valid5 = "-2,0";

        CHECK(Parser::IsNumber(valid1));
        CHECK(Parser::IsNumber(valid2));
        CHECK(Parser::IsNumber(valid3));
        CHECK(Parser::IsNumber(valid4));
        CHECK(Parser::IsNumber(valid5));
    }

    SUBCASE("Inválidos")
    {
        std::string invalid1 = "1234131a231321313.443";
        std::string invalid2 = "T1234.443";
        std::string invalid3 = "1234.44.3";
        std::string invalid4 = "a";
        std::string invalid5 = "+";
        std::string invalid6 = "210+";
        std::string invalid7 = "2-10";
        std::string invalid8 = "--";

        CHECK(not Parser::IsNumber(invalid1));
        CHECK(not Parser::IsNumber(invalid2));
        CHECK(not Parser::IsNumber(invalid3));
        CHECK(not Parser::IsNumber(invalid4));
        CHECK(not Parser::IsNumber(invalid5));
        CHECK(not Parser::IsNumber(invalid6));
        CHECK(not Parser::IsNumber(invalid7));
        CHECK(not Parser::IsNumber(invalid8));
    }
}

TEST_CASE("Validar expressão infixa")
{
    SUBCASE("Operador no inicio ou fim")
    {
        CHECK(not Parser::InfixIsValid("+ 1 * 3 - 45"));
        CHECK(not Parser::InfixIsValid("1 * 3.4 + 45 x"));
    }

    SUBCASE("Sequência de operadores no meio da string")
    {
        CHECK(not Parser::InfixIsValid("1 * 3 + - 45"));
    }

    SUBCASE("Sequência de números sem operadores entre eles")
    {
        CHECK(not Parser::InfixIsValid("10 1 * 3 - 45"));
        CHECK(not Parser::InfixIsValid("1 * 3 3 - 45"));
        CHECK(not Parser::InfixIsValid("1 * 3 - 45 0"));
    }

    SUBCASE("Expressão com parênteses inválidos")
    {
        CHECK(not Parser::ParenthesisIsValid("1 * ( 3 - 45"));
        CHECK(not Parser::ParenthesisIsValid("1 * 3 - 45.5 )"));
        CHECK(not Parser::ParenthesisIsValid("( ( 1 * 3 - 45 )"));
        CHECK(not Parser::ParenthesisIsValid("1 * 3 ) - 45 )"));
        CHECK(not Parser::ParenthesisIsValid(") 1 * 3 ( / 5 - 45"));
        CHECK(not Parser::ParenthesisIsValid("1 * ) 3 / 5.3 ( - 45"));
        CHECK(not Parser::ParenthesisIsValid("( 1 * ) ) 3 / 5.3 ( - 45"));
        CHECK(not Parser::ParenthesisIsValid("1 ( * ) 3"));
        CHECK(not Parser::ParenthesisIsValid("1 ( + ) 3"));
        CHECK(not Parser::ParenthesisIsValid("1 * 3 ( / ) 5 - 45"));
    }

    SUBCASE("Expressão infixa válida sem parênteses")
    {
        CHECK(Parser::InfixIsValid("1 * 3 / 5 - 45"));
    }

    SUBCASE("Expressão infixa válida com parênteses")
    {
        CHECK(Parser::InfixIsValid("1 * 3 / ( 5.3 - 45 )"));
    }

    SUBCASE("Expressão infixa inválida '.' como se fosse um número")
    {
        CHECK(not Parser::InfixIsValid("1 * . / 5 - 45"));
        CHECK(not Parser::InfixIsValid("1 * 3 / 5.3 - ."));
    }

    SUBCASE("Expressão infixa inválida '.' como se fosse um número")
    {
        CHECK(not Parser::InfixIsValid("1 * . / 5 - 45"));
        CHECK(not Parser::InfixIsValid("1 * 3 / 5.3 - ."));
    }
}

TEST_CASE("Validar expressão posfixa")
{
    SUBCASE("Operador no início da string")
    {
        CHECK(not Parser::PostfixIsValid("+ 1 * 3 - 45"));
    }

    SUBCASE("Operando no fim da string")
    {
        CHECK(not Parser::PostfixIsValid("1 3 * 3 + - 45"));
    }

    SUBCASE("Expressão com três operandos para um operador")
    {
        CHECK(not Parser::PostfixIsValid("3 4 5 +"));
    }

    SUBCASE("Expressão com caracteres inválidos")
    {
        CHECK(not Parser::PostfixIsValid("3 4 - 5 ) - +"));
    }

    SUBCASE("Expressão com '.' como se fosse um número")
    {
        CHECK(not Parser::PostfixIsValid("3 4 . - +"));
    }
}
