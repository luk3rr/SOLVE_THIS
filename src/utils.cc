/*
* Filename: utils.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "utils.h"

namespace utils {
    void defineCommand(const std::string &input, Command &cmd) {
        if (input == "LER")
            cmd = Command::LER;
        else if (input == "LER INFIXA")
            cmd = Command::LER_INFIXA;
        else if (input == "LER POSFIXA")
            cmd = Command::LER_POSFIXA;
        else if (input == "INFIXA")
            cmd = Command::INFIXA;
        else if (input == "POSFIXA")
            cmd = Command::POSFIXA;
        else if (input == "RESOLVE")
            cmd = Command::RESOLVE;
        else if (input == "PRINT")
            cmd = Command::PRINT;
        else if (input == "EXIT")
            cmd = Command::EXIT;
        else if (input == "ANALYZER")
            cmd = Command::ANALYZER;
        else
            cmd = Command::HELP;
    }

    void usage() {
        std::cout << "Resolvedor de Expressão" << std::endl;
        std::cout << "\tLER \t\t<expressão>\tlê uma expressão genérica (posfixa ou infixa)" << std::endl;
        std::cout << "\tLER INFIXA \t<expressão>\tlê uma expressão infixa" << std::endl;
        std::cout << "\tLER POSFIXA \t<expressão>\tlê uma expressão posfixa" << std::endl;
        std::cout << "\tINFIXA \t\t\t\tMostra a expressão armazenada no formato infixa" << std::endl;
        std::cout << "\tPOSFIXA \t\t\tMostra a expressão armazenada no formato posfixa" << std::endl;
        std::cout << "\tRESOLVE \t\t\tResolve a expressão armazenada" << std::endl;
        std::cout << "\tPRINT \t\t\t\tImprime a árvore com a expressão armazenada" << std::endl;
        std::cout << "\tANALYZER \t\t\tExecuta a verificação de desempenho" << std::endl;
        std::cout << "\tEXIT \t\t\t\tFecha o programa" << std::endl;
        std::cout << "\tHELP \t\t\t\tMostra as opções do programa" << std::endl;
    }
}
