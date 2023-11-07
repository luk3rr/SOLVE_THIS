/*
* Filename: expression_tree_calculator.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "expression_tree_calculator.h"

ExpressionTreeCalculator::~ExpressionTreeCalculator()
{
    this->m_expression.DeleteTree();
}

void ExpressionTreeCalculator::StoreExpression(std::string expression)
{
    if (Parser::InfixIsValid(expression))
    {
        expression = Converter::Infix2Postfix(expression);
    }
    else if (not Parser::PostfixIsValid(expression))
    {
        throw psrexcpt::InvalidExpression(expression);
    }

    this->m_expression.DeleteTree();

    slkd::Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token)
    {
        if (Parser::IsNumber(token))
        {
            stack.Push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::IsValidOperator(token))
        {
            stack.Push(new dlkd::Node<std::string>(token, stack.Pop(), stack.Pop()));
        }
    }

    this->m_expression.InsertExistingTree(stack.Pop(), numNodes);
}

void ExpressionTreeCalculator::StoreExpression(std::string expression, std::string type)
{
    if (type == "INFIXA")
    {
        if (Parser::InfixIsValid(expression))
            expression = Converter::Infix2Postfix(expression);

        else
            throw psrexcpt::InvalidExpression(expression);
    }
    else if (type == "POSFIXA")
    {
        if (not Parser::PostfixIsValid(expression))
            throw psrexcpt::InvalidExpression(expression);
    }

    this->m_expression.DeleteTree();

    slkd::Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token)
    {
        if (Parser::IsNumber(token))
        {
            stack.Push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::IsValidOperator(token))
        {
            stack.Push(new dlkd::Node<std::string>(token, stack.Pop(), stack.Pop()));
        }
    }

    this->m_expression.InsertExistingTree(stack.Pop(), numNodes);
}

std::string ExpressionTreeCalculator::Postfix()
{
    slkd::Queue<std::string> walk;
    this->m_expression.PostorderTreeWalk(walk);

    return Converter::Queue2String(walk);
}

std::string ExpressionTreeCalculator::Infix()
{
    slkd::Queue<std::string> walk;
    this->m_expression.PostorderTreeWalk(walk);

    return Converter::Postfix2Infix(walk);
}

void ExpressionTreeCalculator::ShowTree()
{
    try
    {
        std::ofstream output("arvore.txt");
        this->m_expression.DumpTree(output);
        output.close();
        std::cout << "Arvore impressa no arquivo 'arvore.txt'" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "ERRO: " << e.what() << std::endl;
    }
}

double_t ExpressionTreeCalculator::Evaluation()
{
    slkd::Stack<long double> evaluationStack;
    std::string token;
    slkd::Queue<std::string> postfix;
    this->m_expression.PostorderTreeWalk(postfix);

    // A ordem das operacoes e o operando que estiver mais embaixo na pilha com o operando acima
    // essas variaveis sao utilizadas para preservar essa ordem nas operacoes de divisao e subtracao
    double_t leftOperand, rightOperand;

    while (not postfix.IsEmpty())
    {
        token = postfix.Dequeue();

        if (Parser::IsNumber(token))
        {
            evaluationStack.Push(Converter::Str2Double(token));
        }
        else if (Parser::IsValidOperator(token))
        {
            switch (token.at(0))
            {
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
                        throw std::logic_error("Divide by zero");

                    evaluationStack.Push(leftOperand / rightOperand);
                    continue;
            }
        }
    }

    // No fim desse trem todo, vai sobrar apenas um elemento na pilha, o qual e o resultado da expressao
    return evaluationStack.Pop();
}
