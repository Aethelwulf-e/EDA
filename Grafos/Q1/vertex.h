#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#define ul unsigned long

/*
 *		Classe vértice, aqui determino todos os atributos do objeto.
 * 		chave, d e pai são os mesmos atributos do objeto vértice do livro
 * 		do Cormen. Já cor e visitado são alterações minhas. Cor aqui não representa
 * 		o estado de um nó mas sim as cores que o problema da coloração pede. R e B são as cores
 * 		propostas e NULO é um valor que representa a falta de coloração. Isso será útil na resolução
 * 		do problema. Visitado é o campo que representa o estado de um nó, se ele já foi expandido ou não.
 */

enum cores {R, B, NULO};

class vertex {
public:
    ul chave;
    ul d;
    cores cor;
    vertex *pai;
    bool visitado;
    std::vector<vertex*> adj_list;

    vertex(ul);
    ~vertex();

    void make_pair(vertex*);
};

#endif // VERTEX_H
