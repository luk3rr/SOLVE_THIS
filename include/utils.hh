#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>

namespace utils {
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

#endif // UTILS_H_
