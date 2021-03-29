#include "node.h"

#include <iostream>

using std::cout;

node::node(int chave) {
    this->chave   = chave;
    this->esq     = nullptr;
    this->dir     = nullptr;
    this->altura  = 1;
}

void node::desalocarMemoria() {
    node *currentNode = this;
    if(currentNode != nullptr) {
        currentNode->esq->desalocarMemoria();
        currentNode->dir->desalocarMemoria();
        delete currentNode;
    }
}

int node::getChave() {
    return this->chave;
}

int node::numeroFolhas() {
    node *currentNode = this;
    if(currentNode == nullptr) {
        return 0;
    }
    else if(currentNode->esq == nullptr &&
            currentNode->dir == nullptr) {
        return 1;
    }

    return currentNode->esq->numeroFolhas() +
            currentNode->dir->numeroFolhas();
}

int node::getAltura() {
    node *currentNode = this;
    if(currentNode == nullptr) {
        return 0;
    }
    return currentNode->altura;
}

int node::getBalanco() {
    node *currentNode = this;
    if(currentNode == nullptr) {
        return 0;
    }
    return (currentNode->esq->getAltura() -
            currentNode->dir->getAltura());
}

void node::preorder() {
    node *currentNode = this;
    if(currentNode != nullptr) {
        cout << currentNode->chave << " ";
        currentNode->esq->preorder();
        currentNode->dir->preorder();
    }
}

void node::inorder() {
    node *currentNode = this;
    if(currentNode != nullptr) {
        currentNode->esq->inorder();
        cout << currentNode->chave << " ";
        currentNode->dir->inorder();
    }
}

void node::postorder() {
    node *currentNode = this;
    if(currentNode != nullptr) {
        currentNode->esq->postorder();
        currentNode->dir->postorder();
        cout << currentNode->chave << " ";
    }
}

node* node::min() {
    node *currentNode = this;

    if(currentNode == nullptr) {
        return nullptr;
    }

    while(currentNode->esq != nullptr) {
        currentNode = currentNode->esq;
    }
    return currentNode;
}

node* node::max() {
    node *currentNode = this;

    if(currentNode == nullptr) {
        return nullptr;
    }

    while(currentNode->dir != nullptr) {
        currentNode = currentNode->dir;
    }
    return currentNode;
}

node* node::minValueNode(node *x) {
    node *currentNode = x;
    while(currentNode->esq != nullptr) {
        currentNode = currentNode->esq;
    }
    return currentNode;
}

node* node::rotacao_dir(node *y) {
    node *x = y->esq;
    node *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    x->altura = std::max(x->esq->getAltura(), x->dir->getAltura()) + 1;
    y->altura = std::max(y->esq->getAltura(), y->dir->getAltura()) + 1;

    return x;
}

node* node::rotacao_esq(node *x) {
    node *y = x->dir;
    node *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = std::max(x->esq->getAltura(), x->dir->getAltura()) + 1;
    y->altura = std::max(y->esq->getAltura(), y->dir->getAltura()) + 1;

    return y;
}

node* node::insert(int chave) {
    node *currentNode = this;
    if(currentNode == nullptr) {
        return new node(chave);
    }

    if(currentNode->chave == chave) {
        return nullptr;
    }

    else if(chave < currentNode->chave) {
        currentNode->esq = currentNode->esq->insert(chave);
    }

    else {
        currentNode->dir = currentNode->dir->insert(chave);
    }

    currentNode->altura = std::max(currentNode->esq->getAltura(),
                                   currentNode->dir->getAltura()) + 1;

    int balanco_diferenca = currentNode->getBalanco();

    if(balanco_diferenca > 1 &&
            chave < currentNode->esq->chave) {
        return rotacao_dir(currentNode);
    }

    if(balanco_diferenca < -1 &&
            chave > currentNode->dir->chave) {
        return rotacao_esq(currentNode);
    }

    if(balanco_diferenca > 1 &&
            chave > currentNode->esq->chave) {
        currentNode->esq = rotacao_esq(currentNode->esq);
    }

    if(balanco_diferenca < -1 &&
            chave < currentNode->dir->chave) {
        currentNode->dir = rotacao_dir(currentNode->dir);
    }

    return currentNode;
}

node* node::remove(int chave) {
    node *currentNode = this;
    if(currentNode == nullptr) {
        return currentNode;
    }
    if(chave < currentNode->chave) {
        currentNode->esq = currentNode->esq->remove(chave);
    }
    else if(chave > currentNode->chave) {
        currentNode->dir = currentNode->dir->remove(chave);
    }
    else {
        if((currentNode->esq == nullptr) || (currentNode->dir == nullptr)) {
            node *temp = nullptr;
            if(temp == currentNode->esq) {
                temp = currentNode->dir;
            } else {
                temp = currentNode->esq;
            }
            if(temp == nullptr) {
                temp = currentNode;
                currentNode = nullptr;
            } else {
                currentNode = temp;
            }
        } else {
            node *temp = minValueNode(currentNode->dir);
            currentNode->chave = temp->chave;
            currentNode->dir = currentNode->dir->remove(temp->chave);
        }
    }

    if(currentNode == nullptr) {
        return currentNode;
    }

    currentNode->altura = std::max(currentNode->esq->getAltura(),
                                   currentNode->dir->getAltura()) + 1;

    int balanco = currentNode->getBalanco();

    if(balanco > 1 &&
            currentNode->esq->getBalanco() >= 0) {
        return rotacao_dir(currentNode);
    }

    if(balanco > 1 &&
            currentNode->esq->getBalanco() < 0) {
        currentNode->esq = rotacao_esq(currentNode->esq);
        return rotacao_dir(currentNode);
    }

    if(balanco < -1 &&
            currentNode->dir->getBalanco() <= 0) {
        return rotacao_esq(currentNode);
    }

    if(balanco < -1 &&
            currentNode->dir->getBalanco() > 0) {
        currentNode->dir = rotacao_dir(currentNode->dir);
        return rotacao_esq(currentNode);
    }

    return currentNode;
}
