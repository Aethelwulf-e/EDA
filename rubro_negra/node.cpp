#include "node.h"

node::node(int chave, color cor,
           node *esq, node *dir, node *pai) {
    this->chave = chave;
    this->cor   = cor;
    this->esq   = esq;
    this->dir   = dir;
    this->pai   = pai;
}
