#ifndef BINARY_TREE_EXCPT_H_
#define BINARY_TREE_EXCPT_H_

#include <exception>

namespace bntexcpt {
    class NewTreeIsEmpty : public std::exception {
            public:
            const char *what() const throw();
    };

    class TreeIsNotEmpty : public std::exception {
          public:
            const char *what() const throw();
    };
} // namespace bntexcpt

#endif // BINARY_TREE_EXCPT_H_
