#include "expression_tree_calculator.hh"

ExpressionTreeCalculator::~ExpressionTreeCalculator() {
    this->_expression.deleteTree();
}

void ExpressionTreeCalculator::storeExpression(std::string expression) {
    if (Parser::infixIsValid(expression)) {
        expression = Converter::infix2Postfix(expression);
    }
    else if (!Parser::postfixIsValid(expression)) {
        throw psrexcpt::InvalidExpression(expression);
    }

    this->_expression.deleteTree();

    Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            stack.push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::isValidOperator(token)) {
            stack.push(new dlkd::Node<std::string>(token, stack.pop(), stack.pop()));
        }
    }
    this->_expression.insertExistingTree(stack.pop(), numNodes);
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

    this->_expression.deleteTree();

    Stack<dlkd::Node<std::string>*> stack;
    int numNodes = expression.size();
    std::string token;

    std::istringstream iss(expression);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            stack.push(new dlkd::Node<std::string>(token));
        }
        else if (Parser::isValidOperator(token)) {
            stack.push(new dlkd::Node<std::string>(token, stack.pop(), stack.pop()));
        }
    }
    this->_expression.insertExistingTree(stack.pop(), numNodes);
}

std::string ExpressionTreeCalculator::postfix() {
    slkd::Queue<std::string> walk;
    this->_expression.postorderTreeWalk(walk);
    return Converter::queue2String(walk);
}

std::string ExpressionTreeCalculator::infix() {
    slkd::Queue<std::string> walk;
    this->_expression.postorderTreeWalk(walk);
    return Converter::postfix2Infix(walk);
}

void ExpressionTreeCalculator::showTree() {
    try {
        std::ofstream output("arvore.txt");
        this->_expression.dumpTree(output);
        output.close();
        std::cout << "Arvore impressa no arquivo 'arvore.txt'" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "ERRO: " << e.what() << std::endl;
    }
}

long double ExpressionTreeCalculator::evaluation() {
    Stack<long double> evaluationStack;
    std::string token;
    slkd::Queue<std::string> postfix;
    this->_expression.postorderTreeWalk(postfix);

    // A ordem das operacoes e o operando que estiver mais embaixo na pilha com o operando acima
    // essas variaveis sao utilizadas para preservar essa ordem nas operacoes de divisao e subtracao
    long double leftOperand, rightOperand;

    while (!postfix.isEmpty()) {
        token = postfix.dequeue();
        if (Parser::isNumber(token)) {
            evaluationStack.push(Converter::str2Double(token));
        }
        else if (Parser::isValidOperator(token)) {
            switch (token.at(0)) {
                case '+':
                    evaluationStack.push(evaluationStack.pop() + evaluationStack.pop());
                    continue;

                case '-':
                    rightOperand = evaluationStack.pop();
                    leftOperand = evaluationStack.pop();
                    evaluationStack.push(leftOperand - rightOperand);
                    continue;

                case '*':
                    evaluationStack.push(evaluationStack.pop() * evaluationStack.pop());
                    continue;

                case '/':
                    rightOperand = evaluationStack.pop();
                    leftOperand = evaluationStack.pop();
                    if (rightOperand == 0)
                        throw clcexcpt::DivisionByZero();

                    evaluationStack.push(leftOperand / rightOperand);
                    continue;
            }
        }
    }
    // No fim desse trem todo, vai sobrar apenas um elemento na pilha, o qual e o resultado da expressao
    return evaluationStack.pop();
}
