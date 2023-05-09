#include "parser_excpt.hh"

psrexcpt::InvalidExpression::InvalidExpression(std::string expression) {
    this->msg = "ERRO: " + expression + " NAO VALIDA";
}

const char* psrexcpt::InvalidExpression::what() const throw() {
    return this->msg.c_str();
}
