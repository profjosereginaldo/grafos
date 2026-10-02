#include "grafo_lista.h"

#ifndef ORDENACAO_TOPOLOGICA_H
#define ORDENACAO_TOPOLOGICA_H

void ordenar_dfs(GrafoLista *g, int *visitado, int *ordenacao);
void buscar_dfs(GrafoLista *g, int u, int *visitado, int *idx, int *ordenacao);

#endif