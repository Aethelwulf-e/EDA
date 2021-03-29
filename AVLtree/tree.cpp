#include "tree.h"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

tree::tree() {
    cout << "Criando..."              << endl;
    cout << "Enter para continuar..." << endl;
    getchar();
    system("clear");
    raiz = nullptr;
}

tree::~tree() {
    cout << "Deletando..." << endl;
    if(raiz != nullptr) {
        raiz->desalocarMemoria();
    }
    cout << "Enter para continuar..." << endl;
    getchar();
    getchar();
    system("clear");
}

int tree::numeroFolhas() {
    if(raiz == nullptr) {
        return 0;
    }
    return raiz->numeroFolhas();
}

int tree::altura() {
    if(raiz == nullptr) {
        return 0;
    }
    return raiz->getAltura();
}

void tree::pre_ordem() {
    if(raiz == nullptr) {
        cout << "Arvore vazia.";
    } else {
        raiz->preorder();
    }
    cout << endl;
}

void tree::em_ordem() {
    if(raiz == nullptr) {
        cout << "Arvore vazia.";
    } else {
        raiz->inorder();
    }
    cout << endl;
}

void tree::pos_ordem() {
    if(raiz == nullptr) {
        cout << "Arvore vazia.";
    } else {
        raiz->postorder();
    }
    cout << endl;
}

node* tree::min() {
    if(raiz == nullptr) {
        return nullptr;
    }
    return raiz->min();
}

node* tree::max() {
    if(raiz == nullptr) {
        return nullptr;
    }
    return raiz->max();
}

void tree::inserir(int chave) {
    if(raiz == nullptr) {
        raiz = new node(chave);
    } else {
        raiz = raiz->insert(chave);
    }
}

void tree::remover(int chave) {
    if(raiz != nullptr) {
        raiz = raiz->remove(chave);
    }
}
