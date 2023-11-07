/*
* Filename: converter.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "converter.h"
#include "parser.h" // incluído aqui devido ao problema de inclusão recursiva

double_t Converter::Str2Double(std::string &str)
{
    Converter::Comma2DotDecimalConverter(str);
    return std::stod(str);
}

void Converter::Comma2DotDecimalConverter(std::string &str)
{
    try
    {
        str.replace(str.find(","), 1, ".");
    }
    catch (std::out_of_range &e)
    {
        // caractere ',' nao foi encontrado na string
        return;
    }
}

void Converter::Dot2CommaDecimalConverter(std::string &str)
{
    try
    {
        str.replace(str.find("."), 1, ",");
    }
    catch (std::out_of_range &e)
    {
        // caractere '.' nao foi encontrado na string
        return;
    }
}

int8_t Converter::Precedence(const std::string &str)
{
    switch (str.at(0))
    {
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

std::string Converter::Infix2Postfix(std::string str)
{
    // Essa função foi implementada a partir da ideia do algoritmo "Shunting Yard",
    // proposto por Edsgar Dijkstra

    slkd::Stack<std::string> simbols;
    std::string token, output;
    std::istringstream iss(str);

    while (iss >> token)
    {
        if (Parser::IsNumber(token))
        {
            Converter::Comma2DotDecimalConverter(token);
            output += token + " ";
        }
        else if (Parser::IsValidOperator(token))
        {
            try
            {
                // Enquanto a precedência do último operador lido na string for menor ou igual a precedência do operador
                // no topo da pilha, mova este operador no topo para a fila output
                while (Converter::Precedence(token) <= Converter::Precedence(simbols.Peek()))
                    output += simbols.Pop() + " ";

                simbols.Push(token);
            }
            catch (stkexcpt::StackIsEmpty &e)
            {
                simbols.Push(token);
                continue;
            }
        }
        else if (token == "(")
        {
            // O primeiro parenteses encontrado é enviado para a pilha de símbolos para sabermos quais são os limites das
            // precedências
            simbols.Push(token);
            continue;
        }
        else if (token == ")")
        {
            // O fechamento de parenteses indica o fim da precedência. Assim os operadores que estão na pilha podem ser
            // desempilhados e enviados à fila
            try
            {
                while (simbols.Peek() != "(")
                    output += simbols.Pop() + " ";

                simbols.Pop();
            }
            catch (.../*stkexcpt::StackIsEmpty &e*/)
            {
                continue;
            }
            // Descarta o parênteses que estava em simbols
        }
    }

    while (not simbols.IsEmpty())
    {
        // Em certos casos pode haver operadores na pilha de simbolos após a leitura da string terminar nesse caso esses
        // operadores podem ser desempilhados e enviados ao fim da expressão posfixa
        output += simbols.Pop() + " ";
    }

    // Remove o espaço em branco no fim da string
    if (not output.empty() and output.back() == ' ')
        output.erase(output.size() - 1);

    return output;
}

std::string Converter::Postfix2Infix(slkd::Queue<std::string> &postfix)
{
    slkd::Stack<std::string> aux;
    std::string token, leftOperand, rightOperand;

    while (not postfix.IsEmpty())
    {
        token = postfix.Dequeue();
        if (Parser::IsNumber(token))
        {
            aux.Push(token);
        }
        else if (Parser::IsValidOperator(token))
        {
            rightOperand = aux.Pop();
            leftOperand = aux.Pop();
            aux.Push("( " + leftOperand + " " + token + " " + rightOperand + " )");
        }
    }

    return aux.Pop();
}

std::string Converter::Postfix2Infix(std::string postfix)
{
    slkd::Stack<std::string> aux;
    std::string token, leftOperand, rightOperand;

    std::istringstream iss(postfix);

    while (iss >> token)
    {
        if (Parser::IsNumber(token))
        {
            aux.Push(token);
        }
        else if (Parser::IsValidOperator(token))
        {
            rightOperand = aux.Pop();
            leftOperand = aux.Pop();
            aux.Push("( " + leftOperand + " " + token + " " + rightOperand + " )");
        }
    }

    return aux.Pop();
}

std::string Converter::Queue2String(slkd::Queue<std::string> &queue)
{
    std::string aux;
    while (not queue.IsEmpty())
        aux += queue.Dequeue() + " ";

    if (not aux.empty() and aux.back() == ' ')
        aux.erase(aux.size() - 1);

    return aux;
}
