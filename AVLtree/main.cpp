// NOME: CARLOS EDUARDO DA SILVA FERREIRA
// MATRICULA: 397611

#include <iostream>
#include <cstdlib>
#include "tree.h"

using namespace std;

void limpaTela() {
    cout << "Enter para continar..." << endl;
    getchar();
    getchar();
    system("clear");
}

int menu() {
    int op = 0;
    cout << "-------------------------------"    << endl;
    cout << "| Implementacao da arvore AVL |"    << endl;
    cout << "-------------------------------"    << endl;
    cout                                         << endl;
    cout << "1 - Inserir"                        << endl;
    cout << "2 - Remover"                        << endl;
    cout << "3 - Percurso pre-ordem"             << endl;
    cout << "4 - Percurso em-ordem"              << endl;
    cout << "5 - Percurso pos-ordem"             << endl;
    cout << "6 - Altura da arvore"               << endl;
    cout << "7 - Numero de folhas da arvore"     << endl;
    cout << "8 - Valor maximo e minimo"          << endl;
    cout << "0 - Sair"                           << endl;
    cout << ">> ";
    cin >> op;

    return op;
}

void init(int op, tree *t, bool *b) {
    system("clear");
    switch(op)
    {
    case 1:
    {
        int novaChave;
        cout << "Entre com o novo valor a ser inserido: ";
        cin >> novaChave;
        t->inserir(novaChave);
        limpaTela();
        break;
    }
    case 2:
    {
        int deleteChave;
        cout << "Entre com o valor que deseja deletar: ";
        cin >> deleteChave;
        t->remover(deleteChave);
        limpaTela();
        break;
    }
    case 3:
    {
        t->pre_ordem();
        limpaTela();
        break;
    }
    case 4:
    {
        t->em_ordem();
        limpaTela();
        break;
    }
    case 5:
    {
        t->pos_ordem();
        limpaTela();
        break;
    }
    case 6:
    {
        int altura = t->altura();
        cout << "Altura da arvore: " << altura << endl;
        limpaTela();
        break;
    }
    case 7:
    {
        int numFolhas = t->numeroFolhas();
        cout << "Numero de folhas da arvore: " << numFolhas << endl;
        limpaTela();
        break;
    }
    case 8:
    {
        node *max = t->max();
        node *min = t->min();
        if(max == nullptr || min == nullptr) {
            cout << "Valores maximo e minimo nao existem..." << endl;
        } else {
            cout << "Valor maximo: " << max->getChave() << endl;
            cout << "Valor minimo: " << min->getChave() << endl;
        }
        limpaTela();
        break;
    }
    case 0:
    {
        *b = false;
        break;
    }
    default:
    {
        cout << "Opcao invalida..." << endl;
        limpaTela();
        break;
    }
    }
}

int main() {
    tree *t = new tree();
    bool continua = true;

    while(continua) {
        init(menu(), t, &continua);
    }

    delete t;

    return 0;
}
