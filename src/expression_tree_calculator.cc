/*
* Filename: expression_tree_calculator.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "expression_tree_calculator.h"

ExpressionTreeCalculator::~ExpressionTreeCalculator() {
    this->_expression.DeleteTree();
}

void ExpressionTreeCalculator::storeExpression(std::string expression) {
    if (Parser::infixIsValid(expression)) {
        expression = Converter::infix2Postfix(expression);
    }
    else if (!Parser::postfixIsValid(expression)) {
        throw psrexcpt::InvalidExpression(expression);
    }

    this->_expression.DeleteTree();

    slkd::Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            stack.Push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::isValidOperator(token)) {
            stack.Push(new dlkd::Node<std::string>(token, stack.Pop(), stack.Pop()));
        }
    }

    this->_expression.InsertExistingTree(stack.Pop(), numNodes);
}

void ExpressionTreeCalculator::storeExpression(std::string expression, std::string type) {
    if (type == "INFIXA") {
        if (Parser::infixIsValid(expression))
            expression = Converter::infix2Postfix(expression);
        else
            throw psrexcpt::InvalidExpression(expression);
    }
    else if (type == "POSFIXA") {
        if (!Parser::postfixIsValid(expression))
            throw psrexcpt::InvalidExpression(expression);
    }

    this->_expression.DeleteTree();

    slkd::Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            stack.Push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::isValidOperator(token)) {
            stack.Push(new dlkd::Node<std::string>(token, stack.Pop(), stack.Pop()));
        }
    }
    this->_expression.InsertExistingTree(stack.Pop(), numNodes);
}

std::string ExpressionTreeCalculator::postfix() {
    slkd::Queue<std::string> walk;
    this->_expression.PostorderTreeWalk(walk);
    return Converter::queue2String(walk);
}

std::string ExpressionTreeCalculator::infix() {
    slkd::Queue<std::string> walk;
    this->_expression.PostorderTreeWalk(walk);
    return Converter::postfix2Infix(walk);
}

void ExpressionTreeCalculator::showTree() {
    try {
        std::ofstream output("arvore.txt");
        this->_expression.DumpTree(output);
        output.close();
        std::cout << "Arvore impressa no arquivo 'arvore.txt'" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "ERRO: " << e.what() << std::endl;
    }
}

long double ExpressionTreeCalculator::evaluation() {
    slkd::Stack<long double> evaluationStack;
    std::string token;
    slkd::Queue<std::string> postfix;
    this->_expression.PostorderTreeWalk(postfix);

    // A ordem das operacoes e o operando que estiver mais embaixo na pilha com o operando acima
    // essas variaveis sao utilizadas para preservar essa ordem nas operacoes de divisao e subtracao
    long double leftOperand, rightOperand;

    while (!postfix.IsEmpty()) {
        token = postfix.Dequeue();
        if (Parser::isNumber(token)) {
            evaluationStack.Push(Converter::str2Double(token));
        }
        else if (Parser::isValidOperator(token)) {
            switch (token.at(0)) {
                case '+':
                    evaluationStack.Push(evaluationStack.Pop() + evaluationStack.Pop());
                    continue;

                case '-':
                    rightOperand = evaluationStack.Pop();
                    leftOperand = evaluationStack.Pop();
                    evaluationStack.Push(leftOperand - rightOperand);
                    continue;

                case '*':
                    evaluationStack.Push(evaluationStack.Pop() * evaluationStack.Pop());
                    continue;

                case '/':
                    rightOperand = evaluationStack.Pop();
                    leftOperand = evaluationStack.Pop();
                    if (rightOperand == 0)
                        throw clcexcpt::DivisionByZero();

                    evaluationStack.Push(leftOperand / rightOperand);
                    continue;
            }
        }
    }
    // No fim desse trem todo, vai sobrar apenas um elemento na pilha, o qual e o resultado da expressao
    return evaluationStack.Pop();
}
