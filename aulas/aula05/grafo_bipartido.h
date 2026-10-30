#include "grafo_lista.h"

#ifndef GRAFO_BIPARTIDO_H
#define GRAFO_BIPARTIDO_H

typedef struct {
    int u;
    int v;
} Aresta;

int eh_bipartido(GrafoLista *g);
int emparelhamento_guloso(Aresta *a, int m, int n);

#endif