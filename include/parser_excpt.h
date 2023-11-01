/*
* Filename: parser_excpt.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef PARSEREXCPT_H_
#define PARSEREXCPT_H_

#include <exception>
#include <string>

namespace psrexcpt
{
    class InvalidExpression : public std::exception
    {
        private:
            std::string msg;

        public:
            InvalidExpression(std::string expression);
            const char *what() const throw();
    };
} // namespace psrexcpt

#endif // PARSEREXCPT_H_
