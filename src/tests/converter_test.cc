/*
* Filename: converter_test.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "doctest.h"
#include "converter.h"
#include "queue_slkd.h"

TEST_CASE("Conversor separador decimal")
{
    SUBCASE("Ponto para vírgula")
    {
        std::string num = "3.95";
        std::string numConverted = "3,95";
        Converter::Dot2CommaDecimalConverter(num);
        CHECK(num == numConverted);
    }

    SUBCASE("Vírgula para ponto")
    {
        std::string num = "3,95";
        std::string numConverted = "3.95";
        Converter::Comma2DotDecimalConverter(num);
        CHECK(num == numConverted);
    }
}

TEST_CASE("Conversor de str para float")
{
    std::string str1 = "3.90";
    double_t num1 = 3.90;
    std::string str2 = "213.940";
    double_t num2 = 213.940;
    std::string str3 = "10,01";
    double_t num3 = 10.01;

    CHECK(Converter::Str2Double(str1) == num1);
    CHECK(Converter::Str2Double(str2) == num2);
    CHECK(Converter::Str2Double(str3) == num3);
}

TEST_CASE("Validar conversão de posfixa para infixa")
{
    SUBCASE("Método que recebe uma string")
    {
        std::string postfix = " 5 4 + 10 *";
        std::string infixExpected = "( ( 5 + 4 ) * 10 )";
        std::string converted = Converter::Postfix2Infix(postfix);
        CHECK(infixExpected == converted);
    }
}

TEST_CASE("Validar conversão de infixa para posfixa")
{
    SUBCASE("Sem parênteses")
    {
        std::string infix = "2 + 3 * 5 / 2 + 10.01 - 4 + 1 + 2 * 1";
        std::string postfixExpected = "2 3 5 * 2 / + 10.01 + 4 - 1 + 2 1 * +";
        std::string converted = Converter::Infix2Postfix(infix);
        CHECK(postfixExpected == converted);
    }

    SUBCASE("Um par de parênteses")
    {
        std::string infix = "3 + 4 * 2 / ( 1 - 5.99 )";
        std::string postfixExpected = "3 4 2 * 1 5.99 - / +";
        std::string converted = Converter::Infix2Postfix(infix);
        CHECK(postfixExpected == converted);
    }

    SUBCASE("Dois pares de parênteses")
    {
        std::string infix = "3 + 4 * 2 / ( 1 - ( 5 + 2.18 ) )";
        std::string postfixExpected = "3 4 2 * 1 5 2.18 + - / +";
        std::string converted = Converter::Infix2Postfix(infix);
        CHECK(postfixExpected == converted);
    }

    SUBCASE("Multiplos pares de parênteses")
    {
        std::string infix = "( 3.02 + 4 ) * 2 / ( 1 - ( 5 + 2.89 ) )";
        std::string postfixExpected = "3.02 4 + 2 * 1 5 2.89 + - /";
        std::string converted = Converter::Infix2Postfix(infix);
        CHECK(postfixExpected == converted);
    }
}
