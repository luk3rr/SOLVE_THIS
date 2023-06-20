/*
* Filename: converter.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <string>
#include <stdexcept>
#include <sstream>

#include "queue_singly_linked.h"
#include "stack_singly_linked.h"

class Converter {
    public:
        /**
        @brief Converte o separador decimal de 'virgula' (notacao europeia) para 'ponto' (notacao americana)
        @param str String que será convertida
        */
        static void comma2DotDecimalConverter(std::string &str);

        /**
        @brief Converte o separador decimal de 'ponto' (notacao americana) para 'virgula' (notacao europeia)
        @param str String que sera convertida
        */
        static void dot2CommaDecimalConverter(std::string &str);

        /**
        @brief Converte uma expressão matemática em notação posfixa para notação infixa
        @param postfix Fila com a expressão que será convertida
        @return String com a expressão infixa
        */
        static std::string postfix2Infix(slkd::Queue<std::string> &postfix);

        /**
        @brief Converte uma expressão matemática em notação posfixa para notação infixa
        @param postfix String com a expressão que será convertida
        @return String com a expressão infixa
        */
        static std::string postfix2Infix(std::string postfix);

        /**
        @brief Converte o que está representado em uma fila para uma string
        @param queue Fila com a representação que será convertida
        @return String com a representação
        */
        static std::string queue2String(slkd::Queue<std::string> &queue);

        /**
        @brief Converte a expressão matemática em notação infixa para notação posfixa
        @param infix Expressão infixa que será convertida
        @return Fila que representa a notação posfixa
        */
        static std::string infix2Postfix(std::string infix);

        /**
        @brief Converte uma string em um float
        @param str String que será convertida
        @return Float convertido a partir da string passada como parametro
        */
        static long double str2Double(std::string &str);

        /**
        @brief Verifica a predecência do operador
        @param str String que representa o operador
        @return Valor da precedência do operador
        */
        static int precedence(const std::string &str);
};

#endif // CONVERTER_H_
