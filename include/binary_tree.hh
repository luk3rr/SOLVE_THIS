#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <fstream>
#include <iostream>

#include "queue.hh"
#include "binary_tree_excpt.hh"
#include "node_doubly_linked.hh"

template <typename typeT>
class BinaryTree {
    private:
        dlkd::Node<typeT> *_root;
        int _nodes;

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        @param level Nível do nó atual
        @param node Nó atual
        @param side, deve receber True se o nó está o lado esquerdo ou False, caso o nó esteja do lado direito
        */
        void dumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft);

        /**
        @brief Inserir um novo elemento na árvore
        @param key Chave do novo nó
        @param node Ponteiro para o próximo nó (função recursiva)
        */
        void insert(dlkd::Node<typeT> *&node, typeT key);

        /**
        @brief Deleta toda a árvore
        @param node Nó atual que será deletado a cada chamada recursiva da função
        */
        void deleteTree(dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void inorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void postorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param node Ponteiro para o próximo
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void preorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node);

    public:
        BinaryTree();

        ~BinaryTree();

        /**
        @brief Busca um nó com uma determinada chave e retorna um ponteiro para ele
        @param key Chave que está sendo procurada
        @param node Ponteiro para o próximo nó
        @return Ponteiro para o nó que contém a chave, nullptr caso não exista um nó na árvore com essa chave
        */
        dlkd::Node<typeT> *search(dlkd::Node<typeT> *node, typeT key);

        /**
        @brief Overload para inserir um novo elemento sem o apontador para o nó
        @param key Chave do novo nó
        */
        void insert(typeT key);

        /**
        @brief Insere uma nova árvore já existente
        @param root Ponteiro para a raiz da árvore que será armazenada
        @param nodes Número de nós da árvore
        */
        void insertExistingTree(dlkd::Node<typeT> *root, int nodes);

        /**
        @brief Deleta toda a árvore
        */
        void deleteTree();

        /**
        @brief Realiza o caminhamento in-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void inorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pré-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void preorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento pós-ordem na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void postorderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Realiza o caminhamento por nível na árvore e vai printando os elementos
        */
        void levelOrderTreeWalk();

        /**
        @brief Realiza o caminhamento por nível na árvore
        @param walk Fila em que serão armazenados os itens do caminhamento
        */
        void levelOrderTreeWalk(CircularQueue<typeT> &walk);

        /**
        @brief Imprime a árvore
        @param output Arquivo em que a impressão será feita
        */
        void dumpTree(std::ofstream &output);
};

template<typename typeT>
BinaryTree<typeT>::BinaryTree() {
    this->_root = nullptr;
    this->_nodes = 0;
}

template<typename typeT>
BinaryTree<typeT>::~BinaryTree() {
    this->deleteTree();
}

template<typename typeT>
dlkd::Node<typeT>* BinaryTree<typeT>::search(dlkd::Node<typeT> *node, typeT key) {
    if (node == nullptr or key == node->_key)
        return node;

    if (key < node->_key)
        return this->search(node->_left, key);

    else
        return this->search(node->_right, key);
}

template<typename typeT>
void BinaryTree<typeT>::insert(typeT key) {
    if (this->_root == nullptr) {
        this->_root = new dlkd::Node<typeT>(key);
        this->_nodes++;
    }
    else {
        if (key < this->_root->_key) {
            this->insert(this->_root->_left, key);
        }
        else {
            this->insert(this->_root->_right, key);
        }
    }
}

template <typename typeT>
void BinaryTree<typeT>::insert(dlkd::Node<typeT> *&node, typeT key) {
    if (node == nullptr) {
        node = new dlkd::Node<typeT>(key);
        this->_nodes++;
    }
    else {
        if (key < node->_key) {
            this->insert(node->_left, key);
        }
        else {
            this->insert(node->_right, key);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::insertExistingTree(dlkd::Node<typeT> *root, int nodes) {
    if (this->_root != nullptr and this->_nodes == 0)
        throw bntexcpt::TreeIsNotEmpty();

    if (root == nullptr or nodes < 1)
        throw bntexcpt::NewTreeIsEmpty();

    this->_nodes = nodes + 1;
    this->_root = root;
}

template<typename typeT>
void BinaryTree<typeT>::deleteTree() {
    this->deleteTree(this->_root);
    this->_root = nullptr;
}

template<typename typeT>
void BinaryTree<typeT>::deleteTree(dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->deleteTree(node->_left);
        this->deleteTree(node->_right);
        delete node;
    }
}

template<typename typeT>
void BinaryTree<typeT>::inorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        this->inorderTreeWalk(walk, this->_root->_left);
        walk.enqueue(this->_root->_key);
        this->inorderTreeWalk(walk, this->_root->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::inorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->inorderTreeWalk(walk, node->_left);
        walk.enqueue(node->_key);
        this->inorderTreeWalk(walk, node->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::preorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        walk.enqueue(this->_root->_key);
        this->preorderTreeWalk(walk, this->_root->_left);
        this->preorderTreeWalk(walk, this->_root->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::preorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        walk.enqueue(node->_key);
        this->preorderTreeWalk(walk, node->_left);
        this->preorderTreeWalk(walk, node->_right);
    }
}

template<typename typeT>
void BinaryTree<typeT>::postorderTreeWalk(CircularQueue<typeT> &walk) {
    if (this->_root != nullptr) {
        this->postorderTreeWalk(walk, this->_root->_left);
        this->postorderTreeWalk(walk, this->_root->_right);
        walk.enqueue(this->_root->_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::postorderTreeWalk(CircularQueue<typeT> &walk, dlkd::Node<typeT> *node) {
    if (node != nullptr) {
        this->postorderTreeWalk(walk, node->_left);
        this->postorderTreeWalk(walk, node->_right);
        walk.enqueue(node->_key);
    }
}

template<typename typeT>
void BinaryTree<typeT>::levelOrderTreeWalk() {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.enqueue(this->_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            std::cout << node->_key << " ";
            queue.enqueue(node->_left);
            queue.enqueue(node->_right);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::levelOrderTreeWalk(CircularQueue<typeT> &walk) {
    CircularQueue<dlkd::Node<typeT>*> queue;
    dlkd::Node<typeT> *node;

    queue.enqueue(this->_root);

    while (!queue.isEmpty()) {
        node = queue.pop();
        if (node != nullptr) {
            walk.enqueue(node->_key);
            queue.enqueue(node->_left);
            queue.enqueue(node->_right);
        }
    }
}

template<typename typeT>
void BinaryTree<typeT>::dumpTree(std::ofstream &output) {
    int level = 0;

    if (this->_root != nullptr) {
        output << this->_root->_key;
        this->dumpTree(this->_root->_left, level + 1, "", output, true);
        this->dumpTree(this->_root->_right, level + 1, "", output, false);
    }
}

template<typename typeT>
void BinaryTree<typeT>::dumpTree(dlkd::Node<typeT> *&node, int level, const std::string &vBar, std::ofstream &output, bool sideIsLeft) {
    if (node != nullptr) {
        if (sideIsLeft) {
            output << vBar << "├─── " << node->_key << std::endl;
        }
        else {
            output << vBar << "└─── " << node->_key << std::endl;
        }
        this->dumpTree(node->_left, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, true);
        this->dumpTree(node->_right, level + 1, vBar + (sideIsLeft ? "│    " : "     "), output, false);
    }
}

#endif // BINARY_TREE_H_
