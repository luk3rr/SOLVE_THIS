#include "expression_tree_calculator_excpt.hh"

const char* clcexcpt::DivisionByZero::what() const throw () {
    return "ERRO: A expressão provoca divisão por 0";
}
