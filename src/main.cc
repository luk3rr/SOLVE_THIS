/*
 * Filename: main.cc
 * Created on: May  9, 2023
 * Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "analyzer.h"
#include "expression_tree_calculator.h"
#include "solve_utils.h"

void MainOptions(std::string&              input,
                 bool&                     run,
                 bool&                     expressionOn,
                 ExpressionTreeCalculator& calculator)
{
    sutils::Command   cmd;
    std::string       command, exp, lastToken;
    std::stringstream ss(input);

    if (input.size() > 10 && input.substr(0, 10) == "LER INFIXA")
    {
        ss >> command >> command;
        command = "LER INFIXA";
    }
    else if (input.size() > 11 && input.substr(0, 11) == "LER POSFIXA")
    {
        ss >> command >> command;
        command = "LER POSFIXA";
    }
    else
    {
        ss >> command;
    }

    sutils::DefineCommand(command, cmd);

    switch (cmd)
    {
        case sutils::Command::LER:
            std::getline(ss, exp);
            // Toda expressao posfixa necessariamente termina com um operador
            // Assim pode-se deferenciar uma possivel expressao posfixa de uma expressao
            // infixa
            lastToken = exp.back();
            if (Parser::IsValidOperator(lastToken))
            {
                try
                {
                    calculator.StoreExpression(exp);
                    std::cout << "EXPRESSAO OK: " << exp << std::endl;
                    expressionOn = true;
                }
                catch (psrexcpt::InvalidExpression& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else
            {
                // Não é posfixa, mas talvez seja infixa
                try
                {
                    calculator.StoreExpression(exp);
                    std::cout << "EXPRESSAO OK: " << exp << std::endl;
                    expressionOn = true;
                }
                catch (psrexcpt::InvalidExpression& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            break;

        case sutils::Command::LER_INFIXA:
            std::getline(ss, exp);

            try
            {
                calculator.StoreExpression(exp, "INFIXA");
                std::cout << "EXPRESSAO OK: " << exp << std::endl;
                expressionOn = true;
            }
            catch (psrexcpt::InvalidExpression& e)
            {
                std::cout << e.what() << std::endl;
            }
            break;

        case sutils::Command::LER_POSFIXA:
            std::getline(ss, exp);

            try
            {
                calculator.StoreExpression(exp, "POSFIXA");
                std::cout << "EXPRESSAO OK: " << exp << std::endl;
                expressionOn = true;
            }
            catch (psrexcpt::InvalidExpression& e)
            {
                std::cout << e.what() << std::endl;
            }
            break;

        case sutils::Command::INFIXA:
            if (expressionOn)
                std::cout << "INFIXA: " << calculator.Infix() << std::endl;
            else
            {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;

        case sutils::Command::POSFIXA:
            if (expressionOn)
                std::cout << "POSFIXA: " << calculator.Postfix() << std::endl;
            else
            {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;

        case sutils::Command::RESOLVE:
            if (expressionOn)
                try
                {
                    std::cout << "VAL: " << std::fixed << std::setprecision(6)
                              << calculator.Evaluation() << std::endl;
                }
                catch (std::logic_error& e)
                {
                    std::cout << e.what() << std::endl;
                }
            else
            {
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            }
            break;

        case sutils::Command::PRINT:
            if (expressionOn)
                calculator.ShowTree();
            else
                std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            break;

        case sutils::Command::ANALYZER:
            Analyzer analyzer;
            analyzer.ExpressionTreeCalculatorAnalysis();
            break;

        case sutils::Command::EXIT:
            run = false;
            break;

        case sutils::Command::HELP:
            sutils::Usage();
            break;
    }
}

int main(int argc, char* argv[])
{
    std::string              input;
    ExpressionTreeCalculator calculator;
    bool                     run          = true;
    bool                     expressionOn = false;

    if (argc > 1 && std::string(argv[1]) == "--file")
    {
        // If the --file option is passed as an argument, read the file line by line
        std::ifstream file(argv[2]); // Open the file for reading
        if (file.is_open())
        {
            while (std::getline(file, input))
            {
                MainOptions(input, run, expressionOn, calculator);
            }
            file.close(); // Close the file after reading
        }
        else
        {
            std::cerr << "Error opening the file: " << argv[2] << std::endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        while (run)
        {
            std::getline(std::cin, input);
            MainOptions(input, run, expressionOn, calculator);
        }
    }

    return EXIT_SUCCESS;
}
