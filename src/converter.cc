#include "converter.hh"
#include "parser.hh" // incluído aqui devido ao problema de inclusão recursiva

long double Converter::str2Double(std::string &str) {
    Converter::comma2DotDecimalConverter(str);
    return std::stod(str);
}

void Converter::comma2DotDecimalConverter(std::string &str) {
    try {
        str.replace(str.find(","), 1, ".");
    }
    catch (std::out_of_range &e) {
        // caractere ',' nao foi encontrado na string
        return;
    }
}

void Converter::dot2CommaDecimalConverter(std::string &str) {
    try {
        str.replace(str.find("."), 1, ",");
    }
    catch (std::out_of_range &e) {
        // caractere '.' nao foi encontrado na string
        return;
    }
}

int Converter::precedence(const std::string &str) {
    switch (str.at(0)) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        default:
            return -1;
    }
}

std::string Converter::infix2Postfix(std::string str) {
    // Essa função foi implementada a partir da ideia do algoritmo "Shunting Yard", proposto por Edsgar Dijkstra

    CircularQueue<std::string> output;
    Stack<std::string> simbols;
    std::string token, aux;
    std::istringstream iss(str);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            Converter::comma2DotDecimalConverter(token);
            output.enqueue(token);
        }
        else if (Parser::isValidOperator(token)) {
            try {
                // Enquanto a precedência do último operador lido na string for menor ou igual a precedência do operador
                // no topo da pilha, mova este operador no topo para a fila output
                while (Converter::precedence(token) <= Converter::precedence(simbols.peek()))
                    output.enqueue(simbols.pop());

                simbols.push(token);

            }
            catch (stkexcpt::StackIsEmpty &e) {
                simbols.push(token);
                continue;
            }
        }
        else if (token == "(") {
            // O primeiro parenteses encontrado é enviado para a pilha de símbolos para sabermos quais são os limites das
            // precedências
            simbols.push(token);
            continue;
        }
        else if (token == ")") {
            // O fechamento de parenteses indica o fim da precedência. Assim os operadores que estão na pilha podem ser
            // desempilhados e enviados à fila
            try {
                while (simbols.peek() != "(")
                    output.enqueue(simbols.pop());

                simbols.pop();
            } catch (stkexcpt::StackIsEmpty &e) {
                continue;
            }
            // Descarta o parênteses que estava em simbols
        }
    }
    while (!simbols.isEmpty()) {
        // Em certos casos pode haver operadores na pilha de simbolos após a leitura da string terminar nesse caso esses
        // operadores podem ser desempilhados e enviados ao fim da expressão posfixa
        output.enqueue(simbols.pop());
    }
    return Converter::queue2String(output);
}

std::string Converter::postfix2Infix(CircularQueue<std::string> postfix) {
    Stack<std::string> aux;
    std::string token, leftOperand, rightOperand;

    while (!postfix.isEmpty()) {
        token = postfix.dequeue();
        if (Parser::isNumber(token)) {
            aux.push(token);
        }
        else if (Parser::isValidOperator(token)) {
            rightOperand = aux.pop();
            leftOperand = aux.pop();
            aux.push("( " + leftOperand + " " + token + " " + rightOperand + " )");
        }
    }
    return aux.pop();
}

std::string Converter::postfix2Infix(std::string postfix) {
    Stack<std::string> aux;
    std::string token, leftOperand, rightOperand;

    std::istringstream iss(postfix);

    while (iss >> token) {
        if (Parser::isNumber(token)) {
            aux.push(token);
        }
        else if (Parser::isValidOperator(token)) {
            rightOperand = aux.pop();
            leftOperand = aux.pop();
            aux.push("( " + leftOperand + " " + token + " " + rightOperand + " )");
        }
    }
    return aux.pop();
}

std::string Converter::queue2String(CircularQueue<std::string> queue) {
    std::string aux;
    while (!queue.isEmpty()) {
        aux += queue.dequeue() + " ";
    }
    if (!aux.empty() and aux.back() == ' ')
        aux.erase(aux.size() - 1);
    return aux;
}
