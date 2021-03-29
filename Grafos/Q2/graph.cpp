#include "graph.h"

/*
 * 		Construtor do grafo, recebe um inteiro n e cria uma matriz nxn
 */

graph::graph(int size) {
    this->size = size;
    this->adj_matriz = new int*[size];

    for(int i = 0; i < size; i++) {
        this->adj_matriz[i] = new int[size];
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            this->adj_matriz[i][j] = 0;
        }
    }
}

/*
 * 		Destrutor do grafo, desaloca a memórica alocada para a matriz
 */

graph::~graph() {
    for(int i = 0; i < this->size; i++) {
        delete[] this->adj_matriz[i];
    }
    delete[] this->adj_matriz;
}

/*
 * 		Função insert que recebe dois valores de nó e insere o valor 1 para
 * 		representar a ligação de um nó a outro.
 */

void graph::insert(int chave_1, int chave_2) {
    this->adj_matriz[chave_1][chave_2] = 1;
    this->adj_matriz[chave_2][chave_1] = 1;
}

/*
 * 		Função auxiliar que multiplica duas matrizes.
 */

int** graph::multiplicaMatriz(int **M1, int **M2) {
    int **novaMatriz = new int*[this->size];

    for(int i = 0; i < this->size; i++) {
        novaMatriz[i] = new int[this->size];
    }

    for(int i = 0; i < this->size; i++) {
        for(int j = 0; j < this->size; j++) {
            int somaProd = 0;
            for(int k = 0; k < this->size; k++) {
                somaProd += M1[i][k] * M2[k][j];
            }
            novaMatriz[i][j] = somaProd;
        }
    }

    return novaMatriz;
}

/*
 * 		Função que resolve o problema do 4-ciclo.
 * 		Se temos uma matriz A e a elevamos a n o que temos
 * 		em cada entrada ij da matriz resultante é a quantidade de caminhos de tamanho n
 * 		que parte do vértice i até o vértice j. Logo, se elevamos a matriz de adjacências
 * 		a segunda potência e verificarmos se existe uma entrada diferente da diagonal principal
 *      com valor maior ou igual a 2 significa que encontramos dois caminhos de tamanho dois (diferentes) que vão de um
 *      vértice a outro, o que configura um ciclo de tamanho 4. Por fim, desalocamos a matriz resultante
 * 		da potência de 2.
 * 
 * 
 * 		Complexidade:
 * 
 * 		A multiplicação de matrizes é um algoritmo conhecido que, para matrizes quadradas de mesma ordem n, que é o caso,
 * 		possui complexidade O(n^3), como a função é chamada uma vez temos que sua complexidade é O(n^3).
 * 		Uma vez que temos a matriz de adjacências elevada a 2, precisamos apenas percorrer a matriz uma vez ignorando a diagonal principal
 * 		o que leva tempo O(|V|^2). Portanto a complexidade final do algoritmo é O(|V|^3) + O(|V|^2) = O(|V|^3).
 */

bool graph::temCicloDeTamanho_4() {
    int **potencia_2 = multiplicaMatriz(this->adj_matriz, this->adj_matriz);
    bool temCiclo = false;

    for(int i = 0; i < this->size; i++) {
        for(int j = 0; j < this->size; j++) {
            if(i != j && potencia_2[i][j] >= 2) {
                temCiclo = true;
                break;
            }
        }
        if(temCiclo) {
            break;
        }
    }

    for(int i = 0; i < this->size; i++) {
        delete[] potencia_2[i];
    }
    delete[] potencia_2;

    return temCiclo;
}
