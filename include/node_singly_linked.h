/*
* Filename: node_singly_linked.h
* Created on: May  9, 2023
* Author: Lucas Araújo <araujolucas@dcc.ufmg.br>
*/

#ifndef NODE_SINGLY_LINKED_H_
#define NODE_SINGLY_LINKED_H_

// Singly linked namespace
namespace slkd {
    template <typename typeT>
    struct Node {
        typeT _key;
        Node<typeT> *_next;

        Node(typeT &k) : _key(k), _next(nullptr) {}
        Node(typeT &k, Node *next) : _key(k), _next(next) {}
    };
}

#endif // NODE_SINGLY_LINKED_H_
