#ifndef GRAPH_H
#define GRAPH_H


class graph {
private:
    int size;
    int **adj_matriz;

protected:
    int** multiplicaMatriz(int**, int**);

public:
    graph(int);
    ~graph();

    void insert(int, int);
    bool temCicloDeTamanho_4();
};

#endif // GRAPH_H
