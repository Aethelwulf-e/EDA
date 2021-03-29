#ifndef TREE_H
#define TREE_H

#include "node.h"

class tree
{
private:
    node *raiz;

public:

    tree();
    ~tree();
    int altura();
    int numeroFolhas();
    void pre_ordem();
    void em_ordem();
    void pos_ordem();
    void inserir(int chave);
    void remover(int chave);
    node* min();
    node* max();
};

#endif // TREE_H
