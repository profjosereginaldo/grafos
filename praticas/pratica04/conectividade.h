#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

#include "../pratica01/grafo_lista.h"

typedef struct {
    int origem;
    int destino;
} Aresta;

int *dfs_articulacoes(GrafoLista *g, int *tamanho);
Aresta *detectar_pontes(GrafoLista *g, int *tamanho);

#endif