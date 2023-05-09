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

bool Parser::parentesesOrderIsValid(std::string infix) {
    std::string token;
    std::istringstream iss(infix);
    int valid = 0;

    while (iss >> token) {
        if (token == ")")
            valid--;

        else if (token == "(")
            valid++;

        if (valid == -1)
            return false;
    }
    return true;
}


bool Parser::infixIsValid(std::string infix) {
    // Premissas para a validade da expressão infixa
    // 1. Sempre haverá um operador entre dois números
    // 2. Sempre haverá um námero entre dois operadores
    // 3. O número de abertura de parênteses deve ser igual ao número de fechamento de parênteses
    // 4. O expressão termina com um número

    if (!Parser::parentesesOrderIsValid(infix))
        return false;

    int pendingClosingParentheses = 0;
    std::string token;
    std::istringstream iss(infix);

    // Inicializado como false, pois espera-se que o primeiro token seja um número
    bool lastIsNumber = false;

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            Converter::comma2DotDecimalConverter(token);
            // Verificação da premissa #1
            if (!lastIsNumber) {
                lastIsNumber = true;
                continue;
            }
            else
                return false;
        }
        else if (Parser::isValidOperator(token)) {
            // Verificação da premissa #2
            if (lastIsNumber) {
                lastIsNumber = false;
                continue;
            }
            else
                return false;
        }
        else if (token == "(")
            pendingClosingParentheses++;

        else if (token == ")")
            pendingClosingParentheses--;

        else
            // Expressão contém um caractere que não compõem um número válido, nem é um operador válido e não é parênteses
            return false;
    }
    // Verificação das premissas #3 e #4
    if (pendingClosingParentheses != 0 or !lastIsNumber)
        return false;

    return true;
}

bool Parser::postfixIsValid(std::string postfix) {
    // Premissas para a validade da expressão posfixa
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
    // Verificação da premissa #2
    if (Parser::isNumber(token))
        return false;

    // Verificação da premissa #3
    if (operands - 1 != operators)
        return false;

    return true;
}
