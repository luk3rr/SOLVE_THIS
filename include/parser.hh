#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <sstream>
#include <cctype>

#include "parser_excpt.hh"
#include "converter.hh"

class Parser {
    public:
        /**
        @brief Verifica se a string representa um número válido
        @param str String que será verificada
        @return True caso represente um número válido, False caso contrário
        */
        static bool isNumber(std::string &str);

        /**
        @brief Verifica se o operador é válido
        @param str String que representa o operador
        @return True caso a string represente um operador válido, False caso contrário
        */
        static bool isValidOperator(std::string &str);

        /**
        @brief Verifica se a expressão infixa é válida
        @param infix Expressão que será avalida
        @return True caso a expressão seja válida, False caso contrário
        */
        static bool infixIsValid(std::string infix);

        /**
        @brief Verifica se a expressão posfixa é válida
        @param posfix Expressão que será avalida
        @return True caso a expressão seja válida, False caso contrário
        */
        static bool postfixIsValid(std::string postfix);

        /**
        @brief Verificar se a ordem dos parênteses está correta.
        Por exemplo ) 2 + 3 ( + 2 + 1 não deve ser considerada uma expressão válida
        @param infix Expressão infixa que será avalida
        @return True se a ordem dos parênteses for coerente, False caso contrário
        */
        static bool parenthesisIsValid(std::string infix);
};

#endif // PARSER_H_
