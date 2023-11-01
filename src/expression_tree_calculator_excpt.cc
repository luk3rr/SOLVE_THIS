/*
* Filename: expression_tree_calculator_excpt.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "expression_tree_calculator_excpt.h"

const char* clcexcpt::DivisionByZero::what() const throw ()
{
    return "ERRO: A expressão provoca divisão por 0";
}
