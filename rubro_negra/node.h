#ifndef NODE_H
#define NODE_H

enum color {RED, BLACK};

class node {
public:
    int chave;
    color cor;
    node *esq;
    node *dir;
    node *pai;

    node(int, color, node*, node*, node*);
};

#endif // NODE_H
