#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"

// Nome: Carlos Eduardo da Silva Ferreira.
// Matrícula: 397611

using namespace std;

/*
 * 		Na main abro o arquivo e vou recebendo os valores do arquivo.
 * 		Quando chego no fim de um grafo, chamo a função temCicloDeTamanho_4 que retorna true ou false
 * 		caso o grafo possua ou não um ciclo de tamanho 4.
 */
 
int main()
{
	ifstream file = ifstream("grafos.txt");
	graph *g = nullptr;
	
	if(!file) {
		cout << "Arquivo grafos.txt nao encontrado" << endl;
	} else {
		int n, c1, c2;
		
		while(file >> n) {
			if(n == 0)
				break;
				
			g = new graph(n);
			
			while(file >> c1 >> c2) {
				if(c1 == 0 && c2 == 0)
					break;
					
				g->insert(c1, c2);
			}
			
			if(g->temCicloDeTamanho_4()) {
				cout << "SIM" << endl;
			} else {
				cout << "NAO" << endl;
			}
		}
	}

    delete g;

    return 0;
}
