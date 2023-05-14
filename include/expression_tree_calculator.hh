#ifndef EXPRESSION_TREE_CALCULATOR_H_
#define EXPRESSION_TREE_CALCULATOR_H_

#include <string>
#include <sstream>
#include <string>

#include "binary_tree.hh"
#include "stack_singly_linked.hh"
#include "queue_singly_linked.hh"
#include "parser.hh"
#include "converter.hh"
#include "expression_tree_calculator_excpt.hh"

class ExpressionTreeCalculator {
    private:
        BinaryTree<std::string> _expression;

    public:
        ~ExpressionTreeCalculator();

        /**
        @brief Armazena uma expressão na árvore
        @param expression Expressão que será armazenada
        @throw psrexcpt::InvalidExpression Caso a expressão seja inválida
        */
        void storeExpression(std::string expression);

        /**
        @brief Armazena uma expressão na árvore
        @param expression Expressão que será armazenada
        @param type Notação em que a expressão está representada
        @throw psrexcpt::InvalidExpression Caso a expressão seja inválida
        */
        void storeExpression(std::string expression, std::string type);

        /**
        @brief Representa a expressão armazenada na árvore na forma posfixa
        @return String com a expressão na forma posfixa
        */
        std::string postfix();

        /**
        @brief Representa a expressão armazenada na árvore na forma infixa
        @return String com a expressão na forma infixa
        */
        std::string infix();

        /**
        @brief Imprime a árvore em um arquivo .txt
        */
        void showTree();

        /**
        @brief Resolve a expressão armazenada na árvore
        @return Float com o valor da expressão
        @throw clcexcpt::DivisionByZero Caso ocorra alguma tentativa de divisão por zero
        */
        long double evaluation();
};

#endif // EXPRESSION_TREE_CALCULATOR_H_
