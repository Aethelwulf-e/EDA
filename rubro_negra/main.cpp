// Nome: Carlos Eduardo da Silva Ferreira
// Matrícula: 397611

#include <iostream>
#include <cstdlib>
#include "node.h"

using namespace std;

// Nó sentinela com chave 0, cor preta, pai e filhos esq e dir apontam para ele mesmo.
static node sentinela = {0, BLACK, &sentinela,
                        &sentinela, &sentinela};

// Defino NIL como um ponteiro para sentinela.
#define NIL &sentinela

class RBtree {
private:
    node *raiz;

protected:
    int alturaUtil(node*);
    void preOrderUtil(node*);
    void deleteTree(node*);
    void rotacao_esq(node*);
    void rotacao_dir(node*);
    void insert_fixup(node*);
    void transplante(node*, node*);
    void remove_fixup(node*);
    node* insertBST(node*, node*);
    node* minValue(node*);

public:
    // Construtor simples da classe, apenas seta a raiz para NIL.
    RBtree() {
        cout << "Criando... Enter para continuar" << endl;
        getchar();
        system("clear");
        raiz = NIL;
    }

    // O destrutor usa do método deleteTree(node*) que recebe um ponteiro para um nó arbitrário
    // e apaga as subárvore esquerda e direita desse nó, além dele mesmo. Aqui passo a raiz para deletar tudo.
    ~RBtree() {
        cout << "Deletando..." << endl;
        deleteTree(raiz);
    }

    // alturaUtil(node*) faz o cálculo da altura de um nó arbitrário
    // e em getAltura() passo a raiz para alturaUtil(node*), assim calculando a altura da árvore.
    int getAltura() {
        return alturaUtil(raiz);
    }

    // preOrderUtil(node*) realiza o percurso em pre-ordem para um nó arbitrário
    // e em preOrdem() passo a raiz para preOrderUtil(node*), assim percorrendo começando da raiz.
    void preOrdem() {
        if(raiz == NIL) {
            cout << "Arvore vazia.";
        } else {
            preOrderUtil(raiz);
        }
        cout << endl;
    }

    node* search(int);
    void insert(int);
    void remove(int);

};

/* deleteTree(node*) apaga a árvore por completa, uso este método no destrutor.
   deleteTree(node*) faz um percurso em pós-ordem deletando toda a subárvore esquerda e direita
   de forma recursiva.
*/
void RBtree::deleteTree(node *raiz) {
    if(raiz != NIL) {
        deleteTree(raiz->esq);
        deleteTree(raiz->dir);
        raiz->pai = nullptr;
        delete raiz;
    }
}

// preOrderUtil(node*) percorre em pre-ordem a árvore a partir de um nó recebido como parâmetro.
void RBtree::preOrderUtil(node *raiz) {
    if(raiz != NIL) {
        cout << "Chave: " << raiz->chave << ", ";
        if(raiz->cor == RED) {
            cout << "Cor: rubro;" << endl;
        } else {
            cout << "Cor: negro;" << endl;
        }
        preOrderUtil(raiz->esq);
        preOrderUtil(raiz->dir);
    }
}

// alturaUtil(node*) calcula a altura de um nó passado como parâmetro.
int RBtree::alturaUtil(node *raiz) {
    if(raiz == NIL) {
        return 0;
    } else {
        int h_esq = 1 + alturaUtil(raiz->esq);
        int h_dir = 1 + alturaUtil(raiz->dir);
        return (h_esq > h_dir ? h_esq : h_dir);
    }
}

// Método search(int) procura por um nó na árvore, partindo da raiz.
// Se chave for menor que o valor do nó procuro na esquerda, se for maior procuro na direira,
// se for igual o nó é retornado, assim como em uma bst qualquer.
node* RBtree::search(int chave) {
    node *tmp = raiz;
    while(tmp != NIL) {
        if(chave < tmp->chave) {
            tmp = tmp->esq;
        } else if(chave > tmp->chave) {
            tmp = tmp->dir;
        } else {
            return tmp;
        }
    }
    return NIL;
}

/*
 *
 *         (x)         dir        (y)
 *         / \        <---        / \
 *        a  (y)      --->       (x) c
 *           / \      esq        / \
 *          b   c               a   b
*/

void RBtree::rotacao_esq(node *x) {
    node *y = x->dir; // Seto (y)
    x->dir = y->esq; // Faço a subárvore direita de (x) receber a subárvore esquerda de (y)

    // Se a esquerda de (y) não era nula então devemos atualizar o campo pai do primeiro
    // nó da subárvore (que agora é (x))
    if(y->esq != NIL) {
        y->esq->pai = x;
    }

    // Como troquei (x) por (y), o pai de (y) deve ser atualizado (o pai de (y) agora é seu avô)
    y->pai = x->pai;

    // Se o pai de (x) era nulo então (x) era a raiz
    // logo o atributo node *raiz da árvore deve ser atualizado pois agora é (y)
    if(x->pai == NIL) {
        raiz = y;

    // Agora se o pai de (x) não for nulo então devo verificar se ele é filho esquerdo
    // ou direito de seu pai. Faço isso para atualizar o campo esquerda (ou direita) do pai
    // de (x), que agora deve ser(y)
    } else if(x == x->pai->esq) {
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }


    y->esq = x; // Coloco (x) na esquerda de (y), assim como na imagem
    x->pai = y; // E o pai de (x) agora é (y)
}

// A rotação direita é simétrica a esquerda
void RBtree::rotacao_dir(node *x) {
    node *y = x->esq;
    x->esq = y->dir;

    if(y->dir != NIL) {
        y->dir->pai = x;
    }

    y->pai = x->pai;

    if(x->pai == NIL) {
        raiz = y;
    } else if(x == x->pai->dir) {
        x->pai->dir = y;
    } else {
        x->pai->esq = y;
    }

    y->dir = x;
    x->pai = y;
}

// Este método insere como uma bst normal, sem se importar com as propriedades.
// Elas serão corrigidas em insert_fixup(node *).
node* RBtree::insertBST(node *raiz, node *newNode) {
    if(raiz == NIL) {
        return newNode;
    }
    if(newNode->chave < raiz->chave) {
        node *filho_esq = insertBST(raiz->esq, newNode);
        raiz->esq = filho_esq;
        filho_esq->pai = raiz;
    } else if(newNode->chave > raiz->chave) {
        node *filho_dir = insertBST(raiz->dir, newNode);
        raiz->dir = filho_dir;
        filho_dir->pai = raiz;
    }
    return raiz;
}

/*
 * O algoritmo insert_fixup(node *) recebe o nó que acabou de ser inserido
 * na árvore e realiza as operações necessárias para manter as 5 propriedades da
 * árvore rubro-negra. O algoritmo funciona, basicamente, de rotações e colorações,
 * quando recolorir um nó não resolve o problema, usamos de rotações. Fazendo isso
 * e subindo na árvore até chegar na raiz ou até o problema já estar resolvido.
 *
 * O algoritmo do livro do Cormen verifica 3 casos para saber se um nó está violando ou não
 * as propriedades da árvore rubro-negra, se sim ele faz as alterações necessárias (recolorir/rotacionar)
 * para resolver o problema e então sobe na árvore e verifica o novo nó com as condições do laço.
 *
 * Casos:
 *      caso 1: tio do nó é rubro.
 *              Aqui, mudamos a cor do pai e do tio do nó para negro.
 *              a cor do avô passa para rubro.
 *              Subimos o nó dois níveis (para o avô).
 *
 *      caso 2: tio é negro e o nó é filho direito de seu pai.
 *              Aqui, fazemos uma rotação esquerda no pai do nó
 *              e então subimos o nó um nível (para seu pai).
 *              Depois fazemos uma rotação direira no avô do nó
 *              e fazemos um swap entre as cores do pai e do avô.
 *
 *      caso 3: tio negro e o nó é filho esquerdo de seu pai.
 *              O caso 3 é na verdade uma parte do caso 2.
 *              Aqui apenas fazemos a rotação direita no avô do nó
 *              e fazemos o swap das cores entre o pai e o avô.
 */
void RBtree::insert_fixup(node *ptr) {
    // Aqui crio nós que representarão o avô e o pai do nó ptr
    // inicializo com NIL pois eles mudarão com o laço
    node *pai_ptr = NIL;
    node *avo_ptr = NIL;

    /*
     * Aqui os casos são testados até chegarmos na raiz ou enquanto a propriedade
     * que diz que um nó rubro não pode ter filhos rubros não for satisfeita.
     */
    while(ptr != raiz && ptr->cor == RED && ptr->pai->cor == RED) {
        pai_ptr = ptr->pai;
        avo_ptr = pai_ptr->pai;
        if(pai_ptr == avo_ptr->esq) {
            node *tio_ptr = avo_ptr->dir;
            // Caso 1
            if(tio_ptr->cor == RED) {
                tio_ptr->cor = BLACK;
                pai_ptr->cor = BLACK;
                avo_ptr->cor = RED;
                ptr = avo_ptr;
            // Fim caso 1
            } else {
                // Caso 2
                if(ptr == pai_ptr->dir) {
                    rotacao_esq(pai_ptr);
                    ptr = pai_ptr;
                    pai_ptr = ptr->pai;
                }
                // Caso 3
                rotacao_dir(avo_ptr);
                color tmp = pai_ptr->cor;
                pai_ptr->cor = avo_ptr->cor;
                avo_ptr->cor = tmp;
                ptr = pai_ptr;
                // Fim caso 3
                // Fim caso 2
            }
        } else {
            // caso simétrico (se o pai do nó for filho direito do avô do nó)
            node *tio_ptr = avo_ptr->esq;
            if(tio_ptr->cor == RED) {
                tio_ptr->cor = BLACK;
                pai_ptr->cor = BLACK;
                avo_ptr->cor = RED;
                ptr = avo_ptr;
            } else {
                if(ptr == pai_ptr->esq) {
                    rotacao_dir(pai_ptr);
                    ptr = pai_ptr;
                    pai_ptr = ptr->pai;
                }
                rotacao_esq(avo_ptr);
                color tmp = pai_ptr->cor;
                pai_ptr->cor = avo_ptr->cor;
                avo_ptr->cor = tmp;
                ptr = pai_ptr;
            }
        }
    }
    // Por fim, setamos a cor do da raiz de negro.
    raiz->cor = BLACK;
}

// insert(int) é o método que o usuário tem acesso, ele usa os métodos
// insertBST(node*, node*) para inserir um novo nó e insert_fixup(node*) passando
// o nó que acabou de ser inserido para manter as propriedades da árvore
void RBtree::insert(int chave) {
    node *newNode = new node(chave, RED, NIL, NIL, NIL); // Criando novo nó com a chave passada e a cor vermelha
    raiz = insertBST(raiz, newNode);
    insert_fixup(newNode);
}

// O método retorna o nó com a menor chave de uma subárvore.
// Será usado na remoção, caso o nó tenha 2 filhos.
node* RBtree::minValue(node *ptr) {
    while(ptr->esq != NIL) {
        ptr = ptr->esq;
    }
    return ptr;
}

/*
 * O método de transplante serve para auxiliar na remoção de um nó.
 * O livro do Cormen define transplante como uma sub-rotina que substitui
 * uma subárvore por outra. Quando transplante substitui (u) por (v), o
 * pai de (u) torna-se o pai de (v) e o pai de (u) acaba tendo (v) como filho.
 */
void RBtree::transplante(node *u, node *v) {
    // Este caso trata de (u) ser a raiz
    if(u->pai == NIL) {
        raiz = v;

    // Se (u) for filho esquerdo de seu pai, então a esquerda do pai será (v)
    } else if(u == u->pai->esq) {
        u->pai->esq = v;

    // Senão, a direita será (v)
    } else {
        u->pai->dir = v;
    }

    // Por fim, atualizo o pai de (v)
    v->pai = u->pai;
}

/*
 * O método remove(int) recebe a chave a ser removida e busca no nó correspondente.
 * Depois de encontrado, ele terá sua cor guardada e então será removido como uma
 * remoção qualquer em uma bst, usando o algoritmo de transplante para mover as subárvore
 * para manter a árvore coerente. Se a cor do nó removido era negro então a propriedade altura negra foi
 * violada, obrigando o uso do método remove_fixup(node*) para trazer de volta uma árvore rubro negra correta.
 */
void RBtree::remove(int chave) {
    // Busco no nó na árvore
    node *z = search(chave);
    node *y = z; // Nó auxiliar
    node *x = NIL; // Nó auxiliar
    // Guardo sua cor
    color y_original = y->cor;

    // Início da remoção padrão

    /*
     * Se o nó a ser removido for uma folha, então os dois primeiros
     * condicionais serão executados. Caso o nó tenho pelo menos uma subárvore,
     * apenas um deles será executado, caso possua duas subárvores, apenas o else
     * da linha 369 será executado.
     */
    if(z->esq == NIL) {
        x = z->dir;
        transplante(z, x);
    } else if(z->dir == NIL) {
        x = z->esq;
        transplante(z, z->esq);
    } else {
        y = minValue(z->dir);
        y_original = y->cor;
        x = y->dir;
        if(y->pai == z) {
            x->pai = y;
        } else {
            transplante(y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplante(z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
        delete z;
    }


    // Fim da remoção padrão


    // Se a cor do nó era negra, a altura negra precisa ser corrigida
    if(y_original == BLACK) {
        remove_fixup(x);
    }
}

/*
 * O livro do Cormen garante que observando 4 casos relacionados
 * ao nó removido será suficiente para retomar as propriedades da árvore
 * rubro-negra.
 *
 * Casos:
 *      Caso 1: O irmão do nó é rubro.
 *              Aqui apenas invertemos as cores do irmão e do pai.
 *              Rotacionamos o pai para a esquerda e atualizamos o nó irmão.
 *      Caso 2: O irmão é negro e seus filhos também.
 *              Aqui apenas invertemos a cor do irmão e subimos na árvore
 *
 *      Caso 3: O irmão é negro, seu filho da direita é negro e seu filho
 *              da esquerda é rubro.
 *              Aqui invertemos as cores do irmão e de seu filho esquerdo,
 *              realizamos uma rotação direita no irmão e o atualizamos.
 *              A cor do irmão recebe a cor de seu pai. A cor de seu pai é atualizada
 *              para negro, a direita do irmão também, fazemos uma rotação esquerda no pai
 *              e saimos do laço.
 *
 *      Caso 4: O irmão é negro, seu filho da direita é rubro.
 *              Caso 4 é um subcaso do caso 3, aqui apenas fazemos
 *              a cor do irmão receber a cor de seu pai. A cor de seu pai é atualizada
 *              para negro, a direita do irmão também, fazemos uma rotação esquerda no pai
 *              e saimos do laço.
 */
void RBtree::remove_fixup(node *ptr) {
    while(ptr != raiz && ptr->cor == BLACK) {
        // Caso 1
        if(ptr == ptr->pai->esq) {
            node *irmao = ptr->pai->dir;
            if(irmao->cor == RED) {
                irmao->cor = BLACK;
                ptr->pai->cor = RED;
                rotacao_esq(ptr->pai);
                irmao = ptr->pai->dir;
            }
        // Fim caso 1

            // Caso 2
            if(irmao->esq->cor == BLACK && irmao->dir->cor == BLACK) {
                irmao->cor = RED;
                ptr = ptr->pai;

            // Fim caso 2

              // Caso 3
            } else {
                if(irmao->dir->cor == BLACK) {
                    irmao->esq->cor = BLACK;
                    irmao->cor = RED;
                    rotacao_dir(irmao);
                    irmao = ptr->pai->dir;
                }
                // Caso 4
                irmao->cor = ptr->pai->cor;
                ptr->pai->cor = BLACK;
                irmao->dir->cor = BLACK;
                rotacao_esq(ptr->pai);
                ptr = raiz;
            }
             // Fim caso 3
               // Fim caso 4

        // O senão é simétrico (caso o nó que foi removido era filho esquerdo)
        } else {
            node *irmao = ptr->pai->esq;
            if(irmao->cor == RED) {
                irmao->cor = BLACK;
                ptr->pai->cor = RED;
                rotacao_dir(ptr->pai);
                irmao = ptr->pai->esq;
            }
            if(irmao->dir->cor == BLACK && irmao->esq->cor == BLACK) {
                irmao->cor = RED;
                ptr = ptr->pai;
            } else {
                if(irmao->esq->cor == BLACK) {
                    irmao->dir->cor = BLACK;
                    irmao->cor = RED;
                    rotacao_esq(irmao);
                    irmao = ptr->pai->esq;
                }
                irmao->cor = ptr->pai->cor;
                ptr->pai->cor = BLACK;
                irmao->esq->cor = BLACK;
                rotacao_dir(ptr->pai);
                ptr = raiz;
            }
        }
    }
    // Por fim, setamos a cor do nó para negro
    ptr->cor = BLACK;
}

void limpaTela() {
    cout << "Enter para continar..." << endl;
    getchar();
    getchar();
    system("clear");
}

int menu() {
    int op;
    cout << "-------------------" << endl;
    cout << "Arvore rubro-negra"  << endl;
    cout << "-------------------" << endl;
    cout                          << endl;
    cout << "1 - Inserir"         << endl;
    cout << "2 - Remover"         << endl;
    cout << "3 - Altura"          << endl;
    cout << "4 - Pre Ordem"       << endl;
    cout << "0 - Sair"            << endl;
    cout                          << endl;
    cout << "Entre com a opcao: ";
    cin >> op;
    return op;
}

void init(RBtree *tree, int op, bool *continuar) {
    system("clear");
    switch(op) {
    case 1: {
        int newValue;
        cout << "Entre com o valor que deseja inserir: ";
        cin >> newValue;
        tree->insert(newValue);
        limpaTela();
        break;
    }

    case 2: {
        int rmvValue;
        cout << "Entre com o valor que deseja remover: ";
        cin >> rmvValue;
        tree->remove(rmvValue);
        limpaTela();
        break;
    }

    case 3: {
        int altura = tree->getAltura();
        cout << "Altura da arvore: " << altura << endl;
        limpaTela();
        break;
    }

    case 4: {
        tree->preOrdem();
        limpaTela();
        break;
    }

    case 0: {
        *continuar = false;
        break;
    }

    default: {
        cout << "Opcao invalida!" << endl;
        limpaTela();
        break;
    }
    }
}

int main() {
    RBtree *t = new RBtree();
    bool continuar = true;

    while(continuar) {
        init(t, menu(), &continuar);
    }

    delete t;

    return 0;
}
