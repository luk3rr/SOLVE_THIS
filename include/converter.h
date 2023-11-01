/*
* Filename: converter.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* Converter é a classe responsável por realizar todas as conversões necessárias para manipular
* a expressão numérica, tanto no sentido de conversão entre as notações infixa e posfixa
* como na resolução da expressão propriamente dita.
*/

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <cmath>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <sstream>

#include "queue_slkd.h"
#include "stack_slkd.h"

class Converter
{
    public:
        /**
         * @brief Converte o separador decimal de 'virgula' (notacao europeia) para
         *        'ponto' (notacao americana)
         * @param str String que será convertida
         */
        static void Comma2DotDecimalConverter(std::string &str);

        /**
         * @brief Converte o separador decimal de 'ponto' (notacao americana) para
         *        'virgula' (notacao europeia)
         * @param str String que sera convertida
         */
        static void Dot2CommaDecimalConverter(std::string &str);

        /**
         * @brief Converte uma expressão matemática em notação posfixa para notação infixa
         * @param postfix Fila com a expressão que será convertida
         * @return String com a expressão infixa
         */
        static std::string Postfix2Infix(slkd::Queue<std::string> &postfix);

        /**
         * @brief Converte uma expressão matemática em notação posfixa para notação infixa
         * @param postfix String com a expressão que será convertida
         * @return String com a expressão infixa
         */
        static std::string Postfix2Infix(std::string postfix);

        /**
         * @brief Converte o que está representado em uma fila para uma string
         * @param queue Fila com a representação que será convertida
         * @return String com a representação
         */
        static std::string Queue2String(slkd::Queue<std::string> &queue);

        /**
         * @brief Converte a expressão matemática em notação infixa para notação posfixa
         * @param infix Expressão infixa que será convertida
         * @return Fila que representa a notação posfixa
         */
        static std::string Infix2Postfix(std::string infix);

        /**
         * @brief Converte uma string em um double
         * @param str String que será convertida
         * @return Double convertido a partir da string
         */
        static double_t Str2Double(std::string &str);

        /**
         * @brief Verifica a predecência do operador
         * @param str String que representa o operador
         * @return Valor da precedência do operador
         */
        static int8_t Precedence(const std::string &str);
};

#endif // CONVERTER_H_
