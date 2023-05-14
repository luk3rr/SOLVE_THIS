#include "parser.hh"

bool Parser::isNumber(std::string &str) {
    bool dotInNumber = false;

    for (unsigned int i = 0; i < str.length(); i++) {
        if (std::isdigit(str[i])) {
            continue;
        }
        else if (str[i] == '.' or str[i] == ',') {
            if (str.length() == 1)
                return false;
            if (!dotInNumber)
                dotInNumber = true;
            else
                // Há mais de 1 separador decimal na string
                return false;
        }
        else if (str[i] == '-' or str[i] == '+') {
            if (i == 0) {
                if (str.length() > 1 and std::isdigit(str[i + 1]))
                    continue;
                else
                    // Encontrou um sinal de magnitude que não está no início da string
                    return false;
            }
            else
                return false;
        }
        else
            // Encontrou algo que não é um digito, nem um separador decimal e nem um sinal de magnitude no ínicio da string
            return false;
    }
    return true;
}

bool Parser::isValidOperator(std::string &str) {
    if (str == "+" or str == "-" or str == "*" or str == "/")
        return true;
    else
        return false;
}

bool Parser::parenthesisIsValid(std::string infix) {
    // Premissas para a verificação da validade dos parênteses em uma expressão:
    // 1. O quantidade de '(' deve ser igual à quantidade de ')'
    // 2. Os parênteses devem estar ordenados, ou seja, uma expressão do tipo '1 + ) 3 - 5 (' não deve ser aceita como válida
    // 3. Dentro dos parênteses deve haver uma subexpressão válida, ou seja, algo do tipo '1 ( + ) 3' não deve ser aceito como válido

    std::string token;
    std::istringstream iss(infix);

    int pendingClosingParenthesis = 0; // Usado rificação da premissa #1
    int orderIsValid = 0; // Usada na verificação da premissa #2
    bool lastIsOpenParenthesis = false; // Usada na verificação da premissa #3

    while (iss >> token) {
        if (token == ")") {
            orderIsValid--;
            pendingClosingParenthesis--;
            lastIsOpenParenthesis = false;
        }
        else if (token == "(") {
            orderIsValid++;
            pendingClosingParenthesis++;
            lastIsOpenParenthesis = true;
        }
        else if (Parser::isValidOperator(token) and lastIsOpenParenthesis)
            return false;

        else if (Parser::isNumber(token) and lastIsOpenParenthesis)
            lastIsOpenParenthesis = false;

        if (orderIsValid == -1)
            return false;
    }
    if (pendingClosingParenthesis != 0)
        return false;

    return true;
}

bool Parser::infixIsValid(std::string infix) {
    // Premissas para a verificação da validade de uma expressão infixa
    // 1. Sempre haverá um operador entre dois números
    // 2. Sempre haverá um número entre dois operadores
    // 3. O número de abertura de parênteses deve ser igual ao número de fechamento de parênteses
    // 4. O expressão termina com um número

    // Verificação da premissa #3 e outros casos de invalidez
    if (!Parser::parenthesisIsValid(infix))
        return false;

    std::string token;
    std::istringstream iss(infix);

    // Inicializado como false, pois espera-se que o primeiro token seja um número
    bool lastIsNumber = false;

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            Converter::comma2DotDecimalConverter(token);
            if (!lastIsNumber) { // Verificação da premissa #1
                lastIsNumber = true;
                continue;
            }
            else
                return false;
        }
        else if (Parser::isValidOperator(token)) {
            if (lastIsNumber) { // Verificação da premissa #2
                lastIsNumber = false;
                continue;
            }
            else
                return false;
        }
        else if (token == "(" or token == ")")
            continue;

        else
            // Expressão contém um caractere que não compõem um número válido, nem é um operador válido e não é parênteses
            return false;
    }
    if (!lastIsNumber) // Verificação das premissas #4
        return false;

    return true;
}

bool Parser::postfixIsValid(std::string postfix) {
    // Premissas para a verificação da validade de uma expressão posfixa
    // 1. A expressão não pode começar com um operador, além disso os dois primeiros tokens da string necessariamente são operandos
    // 2. A expressão não pode terminar com um operando
    // 3. Toda expressao posfixa tem N - 1 operandores, onde N é a quantidade de operandos.

    std::string token;
    int operands, operators;
    operands = operators = 0;
    std::istringstream iss(postfix);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            operands++;
        }
        else if (Parser::isValidOperator(token)) {
            // Verificação da premissa #1
            if (operands == 0 or operands == 1)
                return false;

            operators++;
        }
        else
            // Expressão contém um caractere que não compõem um número válido e nem é um operador válido
            return false;
    }
    if (Parser::isNumber(token)) // Verificação da premissa #2
        return false;

    if (operands - 1 != operators) // Verificação da premissa #3
        return false;

    return true;
}
