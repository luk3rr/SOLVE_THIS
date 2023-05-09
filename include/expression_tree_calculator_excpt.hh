#ifndef EXPRESSION_TREE_CALCULATOR_EXCPT_H_
#define EXPRESSION_TREE_CALCULATOR_EXCPT_H_

#include <exception>

namespace clcexcpt {
    class DivisionByZero : public std::exception {
        public:
            const char *what() const throw();
    };
} // namespace clcexcpt

#endif // EXPRESSION_TREE_CALCULATOR_EXCPT_H_
