#include "vertex.h"

/*
 * 		Construtor da classe vértice, recebe uma chave e cria um nó com tal valor.
 */

vertex::vertex(ul chave) {
    this->chave = chave;
    this->cor = NULO;
    this->d = 0;
    this->pai = nullptr;
    this->visitado = false;
    this->adj_list = std::vector<vertex*>();
}

vertex::~vertex() {}

/*
 * 		A função make_pair recebe o ponteiro para um vértice
 * 		e o insere na lista de adjacências do vértice que chamou o método.
 */
void vertex::make_pair(vertex *v) {
    this->adj_list.push_back(v);
}
