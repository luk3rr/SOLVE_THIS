/*
* Filename: expression_tree_calculator.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*
* ExpressionTreeCalculator é responsável por resolver a expressão numérica
*/

#ifndef EXPRESSION_TREE_CALCULATOR_H_
#define EXPRESSION_TREE_CALCULATOR_H_

#include <cmath>
#include <string>
#include <sstream>
#include <string>

#include "queue_slkd.h"
#include "stack_slkd.h"
#include "binary_tree.h"

#include "parser.h"
#include "converter.h"
#include "expression_tree_calculator_excpt.h"

class ExpressionTreeCalculator
{
    private:
        BinaryTree<std::string> m_expression;

    public:
        ~ExpressionTreeCalculator();

        /**
         * @brief Armazena uma expressão na árvore
         * @param expression Expressão que será armazenada
         * @throw psrexcpt::InvalidExpression Caso a expressão seja inválida
         */
        void StoreExpression(std::string expression);

        /**
         * @brief Armazena uma expressão na árvore
         * @param expression Expressão que será armazenada
         * @param type Notação em que a expressão está representada
         * @throw psrexcpt::InvalidExpression Caso a expressão seja inválida
         */
        void StoreExpression(std::string expression, std::string type);

        /**
         * @brief Representa a expressão armazenada na árvore na forma posfixa
         * @return String com a expressão na forma posfixa
         */
        std::string Postfix();

        /**
         * @brief Representa a expressão armazenada na árvore na forma infixa
         * @return String com a expressão na forma infixa
         */
        std::string Infix();

        /**
         * @brief Imprime a árvore em um arquivo .txt
         */
        void ShowTree();

        /**
         * @brief Resolve a expressão armazenada na árvore
         * @return Float com o valor da expressão
         * @throw clcexcpt::DivisionByZero Caso ocorra alguma tentativa de divisão por zero
         */
        double_t Evaluation();
};

#endif // EXPRESSION_TREE_CALCULATOR_H_
