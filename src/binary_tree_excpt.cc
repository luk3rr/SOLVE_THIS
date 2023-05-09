#include "binary_tree_excpt.hh"

const char* bntexcpt::NewTreeIsEmpty::what() const throw() {
    return "ERRO: Nova árvore inexistente ou vazia";
}

const char* bntexcpt::TreeIsNotEmpty::what() const throw() {
    return "ERRO: A árvore atual não está vazia";
}
