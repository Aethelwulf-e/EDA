#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"

// NOME: CARLOS EDUARDO DA SILVA FERREIRA
// MATRÍCULA: 397611


using namespace std;

/*
 * 		Na main abro o arquivo grafos.txt e leio seus valores como descrito antes no pdf.
 * 		Quando chego no fim de um grafo, chamo a função k_cores que retorna true ou false
 * 		caso o grafo possa ou não ser pintado com duas cores. Se sim mostro a cor final de cada vértice.
 */

int main() {
	ifstream file = ifstream("grafos.txt");
	graph *g = nullptr;
	
	if(!file) {
		cout << "Arquivo grafos.txt nao encontrado" << endl;
	} else {
		ul n, c1, c2;
		
		while(file >> n) {
			if(n == 0)
				break;
				
			g = new graph(n);
			
			while(file >> c1 >> c2) {
				if(c1 == 0 && c2 == 0)
					break;
					
				g->insert(c1, c2);
			}
			
			if(g->k_cores()) {
				cout << "SIM" << endl;
				g->mostrar_cores();
			} else {
				cout << "NAO" << endl;
			}
		}
	}

    delete g;
    
    return 0;
}
