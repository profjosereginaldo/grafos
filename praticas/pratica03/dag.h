#ifndef DAG_H
#define DAG_H

#include "../pratica01/grafo_lista.h"

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

int eh_dag(GrafoLista *g);

#endif