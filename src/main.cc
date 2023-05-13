#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "analyzer.hh"
#include "converter.hh"
#include "expression_tree_calculator_excpt.hh"
#include "parser.hh"
#include "expression_tree_calculator.hh"
#include "parser_excpt.hh"
#include "queue_singly_linked.hh"
#include "utils.hh"

void mainOptions(std::string &input, bool &run, bool &expressionOn, ExpressionTreeCalculator &calculator) {
    utils::Command cmd;
    std::string command, exp, lastToken;
    std::stringstream ss(input);

    if (input.size() > 10 && input.substr(0, 10) == "LER INFIXA") {
        ss >> command >> command;
        command = "LER INFIXA";
    }
    else if (input.size() > 11 && input.substr(0, 11) == "LER POSFIXA") {
        ss >> command >> command;
        command = "LER POSFIXA";
    }
    else {
        ss >> command;
    }

    utils::defineCommand(command, cmd);

    switch (cmd) {
        case utils::Command::LER:
            std::getline(ss, exp);
            // Toda expressao posfixa necessariamente termina com um operador
            // Assim pode-se deferenciar uma possivel expressao posfixa de uma expressao infixa
            lastToken = exp.back();
            if (Parser::isValidOperator(lastToken)) {
                try {
                    calculator.storeExpression(exp);
                    std::cout << "EXPRESSAO OK: " << exp << std::endl;
                    expressionOn = true;
                }
                catch (psrexcpt::InvalidExpression &e) {
                    std::cout << e.what() << std::endl;
                }
            }
            else {
                // Não é posfixa, mas talvez seja infixa
                try {
                    calculator.storeExpression(exp);
                    std::cout << "EXPRESSAO OK: " << exp << std::endl;
                    expressionOn = true;
                }
                catch (psrexcpt::InvalidExpression &e) {
                    std::cout << e.what() << std::endl;
                }
            }
            break;
        case utils::Command::LER_INFIXA:
            std::getline(ss, exp);
            try {
                calculator.storeExpression(exp, "INFIXA");
                std::cout << "EXPRESSAO OK: " << exp << std::endl;
                expressionOn = true;
            }
            catch (psrexcpt::InvalidExpression &e) {
                std::cout << e.what() << std::endl;
            }
            break;
        case utils::Command::LER_POSFIXA:
            std::getline(ss, exp);
            try {
                calculator.storeExpression(exp, "POSFIXA");
                std::cout << "EXPRESSAO OK: " << exp << std::endl;
                expressionOn = true;
            }
            catch (psrexcpt::InvalidExpression &e) {
                std::cout << e.what() << std::endl;
            }
            break;
        case utils::Command::INFIXA:
            if (expressionOn)
                std::cout << "INFIXA: " << calculator.infix() << std::endl;
            else {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;
        case utils::Command::POSFIXA:
            if (expressionOn)
                std::cout << "POSFIXA: " << calculator.postfix() << std::endl;
            else {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;
        case utils::Command::RESOLVE:
            if (expressionOn)
                try {
                    std::cout << "VAL: " << std::fixed << std::setprecision(6) << calculator.evaluation()<< std::endl;
                }
                catch (clcexcpt::DivisionByZero &e) {
                    std::cout << e.what() << std::endl;
                }
            else {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;
        case utils::Command::PRINT:
            if (expressionOn)
                calculator.showTree();
            else
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            break;
        case utils::Command::ANALYZER:
            Analyzer analyzer;
            analyzer.expressionTreeCalculator_analysis();
            break;

        case utils::Command::EXIT:
            run = false;
            break;
        case utils::Command::HELP:
            utils::usage();
            break;
    }
}

int main(int argc, char *argv[]) {
    std::string input;
    ExpressionTreeCalculator calculator;
    bool run = true;
    bool expressionOn = false;

    if (argc > 1 and std::string(argv[1]) == "--file") {
        while (std::getline(std::cin, input)) {
            mainOptions(input, run, expressionOn, calculator);
        }
    }
    else {
        while (run) {
            std::getline(std::cin, input);
            mainOptions(input, run, expressionOn, calculator);
        }
    }
    return 0;
}
