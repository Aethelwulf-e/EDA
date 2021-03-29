#include "graph.h"

#include <iostream>
#include <queue>

/*
 *		Construtor da classe, recebe um unsigned long e cria um vector de vértices.
 * 		com tal quantidade e seta o valor de cada um para 0..size-1
 */

graph::graph(ul size) {
    this->size = size;
    this->V = std::vector<vertex*>(size);

    for(ul i = 0; i < size; i++) {
        V[i] = new vertex(i);
    }
}

/*
 * 		O destrutor deleta o vector de vértices chamando a função clear
 * 		que chama o destrutor de cada objeto dentro da estrutura.
 */

graph::~graph() {
    V.clear();
}

/*
 * 		A função insert recebe dois valores e faz uma busca procurando no vector
 * 		de vértices criado no construtor o vértice certo para receber o valor que será seu
 * 		vizinho. Isso para ambas as chaves.
 */

void graph::insert(ul chave_1, ul chave_2) {
    V[chave_1]->adj_list.push_back(V[chave_2]);
    V[chave_2]->adj_list.push_back(V[chave_1]);
}

/*
 * 		Função principal que resolve o problema proposto. A lógica é: começo pintando todos os vértices
 * 		de NULO, uma cor para determinar que um nó ainda não foi pintado. Então faço uma BFS pelos vértices,
 * 		Se a cor de um nó u que acabei de tirar da fila for nulo então o pinto de R, senão não mudo sua cor.
 * 		Agora, percorrendo cada vizinho v de u, olho para suas cores e comparo com a cor de u, se u for R e
 * 		v for NULO então pinto v de B, senão devo checar a cor de v, se v for R, se for devo retornar falso, pois
 * 		estou tentando mudar a cor de um nó que já possui vizinhos de cores diferentes. Mesma coisa se u for B:
 * 		devo checar se v é NULO, se sim o pinto de R, senão vejo se sua cor é B, se sim retorno falso pelo mesmo motivo.
 * 
 * 		Lembrando que os vértices possuem um atributo chamado de visitado
 * 		que representa as cores WHITE e GRAY do algoritmo BFS do Cormen, chamei de visitado para não serem confundidas
 * 		com as cores do problemas. Outra alteração a respeito da BFS original é que eu sempre olho para todos os vizinhos
 * 		de um nó mesmo que tal vizinho já tenha sido visitado, pois preciso saber sua cor. Note que se um nó já foi visitado
 * 		não será recolocado na fila, logo a complexidade da BFS não aumenta.
 */

bool graph::k_cores() {
    for(vertex *v : this->V) {
        v->cor = NULO;
        v->d = INF;
        v->pai = nullptr;
        v->visitado = false;
    }

    vertex *aux = this->V[0];
    aux->visitado = true;
    aux->d = 0;

    std::queue<vertex*> f = std::queue<vertex*>();

    f.push(aux);

    while(!f.empty()) {
        vertex *u = f.front();
        f.pop();

        if(u->cor == NULO) {
            u->cor = R;
        }

        for(vertex *v : u->adj_list) {
            if(!v->visitado)
                f.push(v);

            v->visitado = true;
            v->d = u->d + 1;
            v->pai = u;

            if(u->cor == R) {
                if(v->cor == NULO) {
                    v->cor = B;
                } else {
                    if(v->cor == R) {
                        return false;
                    }
                }
            }

            if(u->cor == B) {
                if(v->cor == NULO) {
                    v->cor = R;
                } else {
                    if(v->cor == B) {
                        return false;
                    }
                }
            }

        }
    }

    return true;
}

/*
 * 		Como cor é um atributo do vértice, para mostrar suas cores apenas preciso
 * 		percorrer o vector de vértices acessando o atributo cor.
 */

void graph::mostrar_cores() {
    for(vertex *v : this->V) {
        std::cout << v->chave << " ";
        if(v->cor == R) {
            std::cout << "R" << std::endl;
        } else if (v->cor == B){
            std::cout << "B" << std::endl;
        } else {
			std::cout << "NULO" << std::endl;
        }
    }
}
