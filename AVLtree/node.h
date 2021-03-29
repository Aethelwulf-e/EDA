#ifndef NODE_H
#define NODE_H


class node
{
private:
    int chave;
    int altura;

public:
    node *esq;
    node *dir;

    node(int chave);
    int getChave();
    int numeroFolhas();
    int getAltura();
    int getBalanco();
    void preorder();
    void inorder();
    void postorder();
    void desalocarMemoria();
    node* rotacao_dir(node *x);
    node* rotacao_esq(node *x);
    node* insert(int chave);
    node* remove(int chave);
    node* minValueNode(node *x);
    node* min();
    node* max();
};

#endif // NODE_H
