#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include <limits>

#define INF std::numeric_limits<int>::max()

class graph {
private:
    unsigned long size;
    std::vector<vertex*> V;

public:
    graph(ul);
    ~graph();

    void insert(ul, ul);
    void mostrar_cores();
    bool k_cores();
};

#endif // GRAPH_H
