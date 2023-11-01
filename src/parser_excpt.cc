/*
* Filename: parser_excpt.cc
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#include "parser_excpt.h"

psrexcpt::InvalidExpression::InvalidExpression(std::string expression)
{
    this->msg = "ERRO: " + expression + " NAO VALIDA";
}

const char* psrexcpt::InvalidExpression::what() const throw()
{
    return this->msg.c_str();
}
