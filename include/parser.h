/*
* Filename: parser.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Parser é responsável por validar os dados manipulados pelo programa, impedindo que
* erros sejam gerados ao tentar resolver/manipular a expressão fornecida pelo usuário.
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <sstream>
#include <cctype>
#include <cstdint>

#include "converter.h"
#include "parser_excpt.h"

class Parser
{
    public:
        /**
         * @brief Verifica se a string representa um número válido
         * @param str String que será verificada
         * @return True caso represente um número válido, False caso contrário
         */
        static bool IsNumber(std::string &str);

        /**
         * @brief Verifica se o operador é válido
         * @param str String que representa o operador
         * @return True caso a string represente um operador válido, False caso contrário
         */
        static bool IsValidOperator(std::string &str);

        /**
         * @brief Verifica se a expressão infixa é válida
         * @param infix Expressão que será avalida
         * @return True caso a expressão seja válida, False caso contrário
         */
        static bool InfixIsValid(std::string infix);

        /**
         * @brief Verifica se a expressão posfixa é válida
         * @param posfix Expressão que será avalida
         * @return True caso a expressão seja válida, False caso contrário
         */
        static bool PostfixIsValid(std::string postfix);

        /**
         * @brief Verificar se a ordem dos parênteses está correta.
         *        Por exemplo ) 2 + 3 ( + 2 + 1 não deve ser considerada uma expressão válida
         * @param infix Expressão infixa que será avalida
         * @return True se a ordem dos parênteses for coerente, False caso contrário
         */
        static bool ParenthesisIsValid(std::string infix);
};

#endif // PARSER_H_
