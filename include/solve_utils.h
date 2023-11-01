/*
* Filename: solve_utils.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef SOLVE_UTILS_H_
#define SOLVE_UTILS_H_

#include <string>
#include <iostream>

namespace sutils {
    enum class Command {
        LER,
        LER_INFIXA,
        LER_POSFIXA,
        INFIXA,
        POSFIXA,
        RESOLVE,
        PRINT,
        EXIT,
        ANALYZER,
        HELP,
    };

    void defineCommand(const std::string &input, Command &cmd);

    void usage();
}

#endif // SOLVE_UTILS_H_
